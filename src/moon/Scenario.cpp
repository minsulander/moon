#include "Scenario.h"
#include "ObjectFactory.h"
#include <mlog/Log.h>
#include "XMLParser.h"
#include "objects/Camera.h"
#include "Interpreter.h"
#include "NetworkMessages.h"
#include "NodeMask.h"
#include "moon/objects/Vehicle.h"
#include <moonet/NetworkManager.h>
#include <osgDB/FileUtils>
#include <osg/io_utils>

using namespace moonet;
using namespace mlog;

namespace moon {

	REGISTER_Object(moon, Scenario);

	Scenario::Scenario()
	:	ComponentContainer(),
		SimulationListener(false),
		realized(false),
                displayMode(BaseObject::DISPLAY_NORMAL),
                manipulator(false)
	{
		rootnode = new osg::Group;
		shadowGroup = new osg::Group;
		shadowGroup->setName("Shadow group");
		rootnode->addChild(shadowGroup.get());
	}

	Scenario::Scenario(const Scenario& scenario, const osg::CopyOp& copyop)
	:	ComponentContainer(scenario, copyop),
		SimulationListener(false),
		realized(false),
                displayMode(scenario.displayMode),
                manipulator(scenario.manipulator)
	{
		/// \todo implement
	}

	void Scenario::parseXML(const TiXmlElement *root)
	{
		//=== Scenario
		//=Scenario specification. Among other things, it specifies which objects participate in a scenario (and how,
		//=for networked games etc.)
		dout(1) << "Parsing scenario " << getName() << "\n";

		ComponentContainer::parseXML(root);

		for (const TiXmlElement *element = root->FirstChildElement(); element; element = element->NextSiblingElement()) {
			if (std::string(element->Value()) == "objects") {
				//=* element: objects
				//=. Objects that participate in the scenario.
				//=** attribute: netmode="server|client|clientonly|serveronly|common|standalone" default "server"
				//=. Specifies how the objects in this list are replicated across the network.
				bool create = false;
				bool construct = false;
				NetworkManager& netman = NetworkManager::instance();
				std::string netmodeStr = XMLParser::parseStringAttribute(element, "netmode", true, "server");
				NetworkMode netmode;
				if (netmodeStr == "server")
					netmode = SERVER;
				else if (netmodeStr == "client")
					netmode = CLIENT;
				else if (netmodeStr == "serveronly")
					netmode = SERVER_ONLY;
				else if (netmodeStr == "clientonly")
					netmode = CLIENT_ONLY;
				else if (netmodeStr == "common")
					netmode = COMMON;
				else if (netmodeStr == "standalone")
					netmode = STANDALONE;
				else
					throw ParseException("Invalid netmode specified", element);
				if ( (netmode == SERVER && (!netman.isActive() || netman.isServer())) ||
					(netmode == CLIENT && (!netman.isActive() || netman.isClient())) ||
					(netmode == CLIENT_ONLY && netman.isActive() && netman.isClient()) ||
					(netmode == SERVER_ONLY && netman.isServer()) ) {
					create = true;
					if (netman.isServer() || netman.isActive())
						construct = true;
				} else if ( netmode == COMMON || (netmode == STANDALONE && !netman.isActive()) ) {
					create = true;
					construct = false;
				}
				bool spawn = XMLParser::parseBooleanAttribute(element, "spawn", true, false);
				dout(3) << "Objects for network mode " << netmodeStr << ":" << (create ? " create" : "") << (construct ? " construct" : "") << (spawn ? " spawn" : "") << "\n";
				if (!create) {
					dout(3) << "Skipping objects for network mode " << netmodeStr << "\n";
					continue;
				}
				ObjectFactory::ObjectList objects = ObjectFactory::instance().parseObjects(element);
				for (ObjectFactory::ObjectList::iterator it = objects.begin(); it != objects.end(); it++) {
					if (spawn)
						spawnObjects.push_back(dynamic_cast<BaseObject*>(it->get()));
					else
						addComponent(dynamic_cast<Component*>(it->get()), construct);
					networkMode[it->get()] = netmode;
				}
			}
		}
                std::string str;
                if (XMLParser::parseStringAttribute(str, root, "manipulator")) {
                    if (str == "camera")
                        manipulator = 0;
                    else if (str == "trackball")
                        manipulator = 1;
                    else if (str == "flight")
                        manipulator = 2;
                    else if (str == "drive")
                        manipulator = 3;
                    else if (str == "terrain")
                        manipulator = 4;
                    else
                        throw ParseException("Invalid 'manipulator' attribute", root);
                }
                if (const TiXmlElement *element = root->FirstChildElement("view")) {
                    osg::Vec3 eye, center, up;
                    up.set(0, 0, 1);
                    XMLParser::parseVector3Attribute(eye, element, "eye");
                    XMLParser::parseVector3Attribute(center, element, "center");
                    XMLParser::parseVector3Attribute(up, element, "up");
                    viewMatrix.makeLookAt(eye, center, up);
                }
                if (const TiXmlElement *element = root->FirstChildElement("earthview")) {
                    osg::Vec3 eye, center, up;
                    double lat, lon, height;
                    lat = XMLParser::parseDoubleAttribute(element, "lat");
                    lon = XMLParser::parseDoubleAttribute(element, "lon");
                    height = XMLParser::parseDoubleAttribute(element, "height");
                    osg::EllipsoidModel *em = TransformObject::getOrCreateEllipsoidModel();
                    double x, y, z;
                    em->convertLatLongHeightToXYZ(lat*M_PI/180.0, lon*M_PI/180.0, height, x, y, z);
                    eye.set(x,y,z);

                    //up = em->computeLocalUpVector(x,y,z);
                    up.set(0,0,1);

                    height = 0.0;
                    XMLParser::parseDoubleAttribute(lat, element, "atlat");
                    XMLParser::parseDoubleAttribute(lon, element, "atlon");
                    XMLParser::parseDoubleAttribute(height, element, "atheight");
                    em->convertLatLongHeightToXYZ(lat*M_PI/180.0, lon*M_PI/180.0, height, x, y, z);
                    center.set(x,y,z);
                    viewMatrix.makeLookAt(eye, center, up);
                }
                dout(3) << "Finished parsing scenario " << getName() << "\n";
	}


	void Scenario::writeXML(TiXmlElement *root) const
	{
		TiXmlComment *comment = new TiXmlComment(" Note: This is a saved scenario ");
		root->LinkEndChild(comment);

		// Save objects for each network mode
		for (int i = 0; i < SPAWN_INSTANCE; i++) {
			ObjectFactory::ObjectList objects;
			for (size_t j = 0; j < getNumComponents(); j++) {
				Component *component = getComponent(j);
				NetworkModeMap::const_iterator it = networkMode.find(component);
				if (it != networkMode.end() && it->second == (NetworkMode)i) {
					objects.push_back(component);
				}
			}
			if (objects.size() > 0) {
				TiXmlElement *element = new TiXmlElement("objects");
				std::string netmodeStr;
				switch (i) {
					case UNKNOWN: netmodeStr = "unknown"; break;
					case SERVER: netmodeStr = "server"; break;
					case CLIENT: netmodeStr = "client"; break;
					case SERVER_ONLY: netmodeStr = "serveronly"; break;
					case CLIENT_ONLY: netmodeStr = "clientonly"; break;
					case COMMON: netmodeStr = "common"; break;
					case STANDALONE: netmodeStr = "standalone"; break;
				}
				element->SetAttribute("netmode", netmodeStr);
				ObjectFactory::instance().writeObjects(objects, element, false);
				root->LinkEndChild(element);
			}
		}

		// Spawn objects
		ObjectFactory::ObjectList objects;
		for (SpawnObjectMap::const_iterator it = allocatedSpawnObjects.begin(); it != allocatedSpawnObjects.end(); it++)
			objects.push_back(it->second.get());
		for (SpawnObjectList::const_iterator it = spawnObjects.begin(); it != spawnObjects.end(); it++)
			objects.push_back(it->get());
		if (objects.size() > 0) {
			TiXmlElement *element = new TiXmlElement("objects");
			element->SetAttribute("netmode","server");
			element->SetAttribute("spawn","true");
			ObjectFactory::instance().writeObjects(objects, element, false);
			root->LinkEndChild(element);
		}

                switch (manipulator) {
                    case 1: root->SetAttribute("manipulator", "trackball"); break;
                    case 2: root->SetAttribute("manipulator", "flight"); break;
                    case 3: root->SetAttribute("manipulator", "drive"); break;
                    case 4: root->SetAttribute("manipulator", "terrain"); break;
                }
                /// \todo save view matrix
	}

	void Scenario::initialize()
	{
		dout(5) << "Initializing scenario " << getName() << "\n";
		// Call lua callback (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::Scenario", "onInitialize")) {
			Interpreter::instance().pushUserType(this, "moon::Scenario");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << "onInitialize script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
		ComponentContainer::initialize();
	}

	void Scenario::reset()
	{
		dout(5) << "Resetting scenario " << getName() << "\n";
		ComponentContainer::reset();
		// Call lua callback (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::Scenario", "onReset")) {
			Interpreter::instance().pushUserType(this, "moon::Scenario");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << "onReset script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
	}

	/// \see BaseObject::realize()
	void Scenario::realize()
	{
		dout(5) << "Realizing scenario " << getName() << "\n";

		ComponentContainer::realize();
		SimulationManager::instance().registerListener(this);
		for (BaseObjectList::iterator it = baseObjects.begin(); it != baseObjects.end(); it++) {
			BaseObject *baseobject = it->get();
			// Make objects available in interpreter objects table
			if (Interpreter::instance().hasLoadedLib("moon")) {
				Interpreter::instance().pushGlobal("objects");
				Interpreter::instance().setTable(baseobject->getName(), baseobject, "moon::BaseObject");
			}
		}
		realized = true;
		currentScenario = this;
		// Call lua callback (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::Scenario", "onRealize")) {
			Interpreter::instance().pushUserType(this, "moon::Scenario");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << "onRealize script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
	}

	void Scenario::unrealize()
	{
		dout(5) << "Unrealizing scenario " << getName() << "\n";
		ComponentContainer::unrealize();
		SimulationManager::instance().unregisterListener(this);
		for (BaseObjectList::iterator it = baseObjects.begin(); it != baseObjects.end(); it++) {
			BaseObject *baseobject = it->get();
			// Make objects unavailable in interpreter objects table
			if (Interpreter::instance().hasLoadedLib("moon")) {
				Interpreter::instance().pushGlobal("objects");
				Interpreter::instance().setTable(baseobject->getName(), NULL, "nil");
			}
		}
		// Remove spawn objects
		while (allocatedSpawnObjects.size() > 0)
			releaseSpawnObject(allocatedSpawnObjects.begin()->first);

		realized = false;
		currentScenario = NULL;
		// Call lua callback (if it exists)
		if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::Scenario", "onUnrealize")) {
			Interpreter::instance().pushUserType(this, "moon::Scenario");
			if (Interpreter::instance().pCall(1,0) != 0)
				dout(ERROR, SCRIPT) << "onUnrealize script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
		}
	}

	void Scenario::update(const double dt)
	{
		ComponentContainer::update(dt);
		for (std::size_t i = 0; i < baseObjects.size(); i++) {
			BaseObject *baseobject = baseObjects[i].get();
			if (baseobject->getRemoveTime() > 1e-5 && SimulationManager::instance().getTime() > baseobject->getRemoveTime()) {
				removeComponent(baseobject);
				i--;
			}
		}
	}

	osg::Group* Scenario::getRootNode()
	{
		rootnode->setName(getName() + " root node");
		return rootnode.get();
	}

	void Scenario::addComponent(Component *component, const bool construct, moonet::Client *owner)
	{
		if (!component) return;
		dout(5) << "Adding " << component->libraryName() << "::" << component->className()
				<< " '" << component->getName() << "' to scenario " << getName() << " " << construct << " " << owner << "\n";
		if (networkMode.find(component) == networkMode.end())
			networkMode[component] = COMMON;
		/// \todo add some kind of remark that the network mode was assumed
		if ( BaseObject *baseobject = dynamic_cast<BaseObject*> (component) ) {
			if (baseobject->getTransform()->getNodeMask() & ( NodeMask::RECEIVE_SHADOW | NodeMask::CAST_SHADOW)) {
				dout(6) << "  to shadowed scene\n";
				shadowGroup->addChild(baseobject->getTransform());
			} else
				rootnode->addChild(baseobject->getTransform());
            assert(baseobject);
			baseObjects.push_back(baseobject);
			Camera *camera;
			if ( !firstCamera && (camera = dynamic_cast<Camera*> (baseobject)) ) {
				firstCamera = camera;
				dout(6) << "  first camera\n";
			}
			if (construct && NetworkManager::instance().isActive()) {
				baseobject->construct();
				if (owner)
					baseobject->setOwner(owner);
			}
			// Make object available in interpreter
			if (Interpreter::instance().hasLoadedLib("moon")) {
				Interpreter::instance().pushGlobal("objects");
				Interpreter::instance().setTable(baseobject->getName(), baseobject, "moon::BaseObject");
				// Call lua callback (if it exists)
				if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::Scenario", "onAddObject")) {
					Interpreter::instance().pushUserType(this, "moon::Scenario");
					Interpreter::instance().pushUserType(baseobject, "moon::BaseObject");
					if (Interpreter::instance().pCall(2,0) != 0)
						dout(ERROR, SCRIPT) << "onAddObject script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
				}
			}
			if (networkMode[component] == COMMON && baseobject->asKinematic() && baseobject->asKinematic()->isDynamic())
				networkMode[component] = SERVER;
		} else if ( Environment *env = dynamic_cast<Environment*> (component) )
			setEnvironment(env);
		ComponentContainer::addComponent(component);
	}

	void Scenario::addComponent(Component *component)
	{
		if (!component) return;
		addComponent(component, false);
	}

	void Scenario::removeComponent(Component *component)
	{
		if (!component) return;
		dout(5) << "Remove " << component->libraryName() << "::" << component->className()
		<< " '" << component->getName() << "' from scenario\n";
		if ( BaseObject *baseobject = dynamic_cast<BaseObject*> (component) ) {
			// Make object unavailable in interpreter
			if (Interpreter::instance().hasLoadedLib("moon")) {
				Interpreter::instance().pushGlobal("objects");
				Interpreter::instance().setTable(baseobject->getName(), NULL, "nil");
				// Call lua callback (if it exists)
				if (Interpreter::initialized && Interpreter::instance().pushMethod(this, "moon::Scenario", "onRemoveObject")) {
					Interpreter::instance().pushUserType(this, "moon::Scenario");
					Interpreter::instance().pushUserType(baseobject, "moon::BaseObject");
					if (Interpreter::instance().pCall(2,0) != 0)
						dout(ERROR, SCRIPT) << "onRemoveObject script for " << getName() << ": " << Interpreter::instance().getError() << "\n";
				}
			}
			if (baseobject == baseobject->getRoot() && baseobject->getTransform()->getNumParents() > 0)
				baseobject->getTransform()->getParent(0)->removeChild(baseobject->getTransform());
			else if (baseobject->getParent())
				baseobject->getParent()->removeChild(baseobject);
			for (BaseObjectList::iterator it = baseObjects.begin(); it != baseObjects.end(); it++) {
				if (baseobject == it->get()) {
					baseObjects.erase(it);
					break;
				}
			}
		}
		ComponentContainer::removeComponent(component);
	}

	void Scenario::setEnvironment(Environment *env)
	{
		if (env == environment.get())
			return;
		if (environment.valid()) {
			osgShadow::ShadowedScene *shadowScene = environment->getShadowedScene();
			if (shadowScene) {
				rootnode->addChild(shadowGroup.get());
				shadowScene->removeChild(shadowGroup.get());
				rootnode->removeChild(shadowScene);
			}
		}
		environment = env;
		if (env) {
			dout(5) << "Applying environment\n";
			environment->apply(rootnode.get());
			osgShadow::ShadowedScene *shadowScene = env->getShadowedScene();
			if (shadowScene) {
				shadowScene->addChild(shadowGroup.get());
				rootnode->removeChild(shadowGroup.get());
				rootnode->addChild(shadowScene);
			}
		} else
			dout(5) << "Null environment\n";
	}

	void Scenario::setDisplayMode(const unsigned int mode)
	{
		for (BaseObjectList::iterator it = baseObjects.begin(); it != baseObjects.end(); it++) {
			BaseObject *baseobject = it->get();
			baseobject->setDisplayMode(mode);
		}
		displayMode = mode;
	}

	void Scenario::spawn(moonet::Player *player)
	{
		osg::ref_ptr<BaseObject> spawnObject = NULL;
		if (!moonet::NetworkManager::instance().isActive()) {
			dout(3) << "Spawning stand-alone player\n";
			if (spawnObjects.size() > 0 && spawnObjects[0].valid()) {
				dout(4) << "Spawn object '" << spawnObjects[0]->getName() << "'\n";
				spawnObject = dynamic_cast<BaseObject*> (spawnObjects[0]->clone(osg::CopyOp::SHALLOW_COPY));
				if (!spawnObject) {
					dout(ERROR) << "Invalid spawn object of type " << spawnObjects[0]->libraryName() << "::" << spawnObjects[0]->className() << "\n";
					return;
				}
			}
		} else if (player && moonet::NetworkManager::instance().isServer()) {
			dout(3) << "Spawning player " << player->getName() << " " << ( player->getOwner() ? player->getOwner()->toString() : "(server)") << "\n";
			if (spawnObjects.size() > 0 && spawnObjects[0].valid()) {
				dout(4) << "Spawn object '" << spawnObjects[0]->getName() << "'\n";
				spawnObject = dynamic_cast<BaseObject*> (spawnObjects[0]->clone(osg::CopyOp::SHALLOW_COPY));
				if (!spawnObject) {
					dout(ERROR) << "Invalid spawn object of type " << spawnObjects[0]->libraryName() << "::" << spawnObjects[0]->className() << "\n";
					return;
				} else
					dout(4) << "  Assigned spawn object '" << spawnObject->getName() << "' to player '" << player->getName() << "', "
							<< spawnObjects.size()-1 << " spawn objects remaining.\n";
			}
		}
		if (spawnObject.valid()) {
			allocatedSpawnObjects[player] = spawnObjects[0].get();
			spawnObjects.erase(spawnObjects.begin());
			addComponent(spawnObject.get(), true, player ? player->getOwner() : NULL);
			if (player == moonet::Player::me()) {
				activateSpawnObject(spawnObject.get(), player);
			} else {
				activeSpawnObjects[player] = spawnObject.get();
				NetworkID objectID = spawnObject->GetNetworkID();
				NetworkManager::instance().sendMessage(MSG_CLIENT_SPAWN_OBJECT, (const char*) &objectID, sizeof(spawnObject->GetNetworkID()), player->getOwner());
			}
			networkMode[spawnObject.get()] = SPAWN_INSTANCE;
		} else
			dout(1) << "No spawn object\n";
	}

	void Scenario::activateSpawnObject(BaseObject *object, moonet::Player *player)
	{
		if (!object) {
			dout(ERROR) << "NULL spawn object\n";
			return;
		}
		activeSpawnObjects[player] = object;
		object->setResetState();
		object->realize();
		if (Vehicle *vehicle = dynamic_cast<Vehicle*> (object)) {
			vehicle->enter();
			dout(4) << "Entering spawn vehicle " << object->getName() << "\n";
		} else if (Camera *cam = dynamic_cast<Camera*> (object)) {
			cam->activate();
			dout(4) << "Activating spawn camera " << cam->getName() << "\n";
		} else
			dout(ERROR) << "Don't know how to activate spawn object '" << object->getName() << "' (" << object->libraryName() << "::" << object->className() << ")\n";
	}

	void Scenario::releaseSpawnObject(moonet::Player *player)
	{
		if (player)
			dout(4) << "Releasing spawn object for player " << player->getName() << "\n";
		{
			SpawnObjectMap::iterator it = allocatedSpawnObjects.find(player);
			if (it == allocatedSpawnObjects.end() || !it->second.valid())
				dout(4) << "  No spawn object found\n";
			else {
				dout(4) << "  Releasing " << it->second->getName() << "\n";
				spawnObjects.insert(spawnObjects.begin(), it->second.get());
				allocatedSpawnObjects.erase(it);
			}
		}
		{
			SpawnObjectObserverMap::iterator it = activeSpawnObjects.find(player);
			if (it != activeSpawnObjects.end() && it->second.valid()) {
				dout(4) << "  Removing " << it->second->getName() << " refcount " << it->second->referenceCount() << "\n";
				removeComponent(it->second.get());
				activeSpawnObjects.erase(it);
			}
		}
	}

	void Scenario::removeRemoteObjects()
	{
		dout(3) << "Removing remote objects\n";
		dout(3) << NetworkManager::instance().isActive() << "\n";
		for (unsigned int i = 0; i < getNumComponents(); i++) {
			NetworkObject *netObject = dynamic_cast<NetworkObject*> (getComponent(i));
			if (netObject && netObject->isRemote()) {
				removeComponent(getComponent(i));
				i--;
			}
		}
	}

	Scenario::~Scenario()
	{
		if (realized)
			unrealize();
		//dout(3) << "~Scenario() " << getName() << " " << this << " refcount " << referenceCount() << "\n";
	}

        osg::observer_ptr<Scenario> Scenario::currentScenario = NULL;

	void ScenarioNetworkObjectListener::setScenario(Scenario *newscenario)
	{
		scenario = newscenario;
		// Network objects might be received before the scenario is loaded, so we place
		// them in a "pending list" temporarily and then transfer them to the scenario.
		if (scenario.valid() && pendingObjects.size() > 0) {
			dout(3, NETWORK) << pendingObjects.size() << " pending network objects for scenario\n";
			for (ObjectList::iterator it = pendingObjects.begin(); it != pendingObjects.end(); it++) {
				scenario->addComponent(dynamic_cast<Component*> (*it), false);
			}
			pendingObjects.clear();
		}
	}

	void ScenarioNetworkObjectListener::onNewObject(NetworkObject *object)
	{
		dout(3, NETWORK) << "New network object " << object->networkObjectName();
		if (scenario.valid()) {
			if (moonet::Player *player = dynamic_cast<moonet::Player*> (object)) {
				if (NetworkManager::instance().isServer()) {
					dout(3, NETWORK) << " is player - spawning...\n";
					scenario->spawn(player);
				}
			} else {
				Component *component = dynamic_cast<Component*> (object);
				if (component) {
					component->initialize();
					dout(3, NETWORK) << " added to scenario\n";
					scenario->addComponent(component, false);
				} else
					dout(3, NETWORK) << " not a component!\n";
			}
		} else {
			dout(3, NETWORK) << " pending\n";
			pendingObjects.push_back(object);
		}
	}

	void ScenarioNetworkObjectListener::onDeleteObject(NetworkObject *object)
	{
		dout(3, NETWORK) << "Delete network object " << object->networkObjectName() << "\n";
		if (scenario.valid()) {
			osg::observer_ptr<Component> component = dynamic_cast<Component*>(object);
			if (component.valid()) {
			  // Note: the object will be deleted by RakNet's replica manager, so we
			  // need to prevent it from being deleted when unreferenced.
			  component->ref();
			  scenario->removeComponent(component.get());
			  component->unref_nodelete();
			}
		} else
			dout(ERROR, NETWORK) << "No scenario when trying to delete network object\n";
	}

	void ScenarioNetworkObjectListener::onPlayerGone(moonet::Player *player)
	{
		if (scenario.valid())
			scenario->releaseSpawnObject(player);
	}

	void ScenarioNetworkObjectListener::onDownloadComplete()
	{
		dout(0, NETWORK) << "Scenario download complete\n";
	}

	bool ScenarioNetworkObjectListener::onMessage(const short id, const char *data, const short len, const bool broadcast)
	{
		dout(1, NETWORK) << "System message: id " << id << " len " << len << "\n";
		switch (id) {
			case MSG_CLIENT_SPAWN_OBJECT: {
				if (!scenario) {
					dout(ERROR, NETWORK) << "Received spawn object with no scenario\n";
					return true;
				}
				NetworkID objectID = *( (NetworkID*) data);
				NetworkObject *object = (NetworkObject*) NetworkManager::instance().getObject(objectID);
				if (object)
					scenario->activateSpawnObject(dynamic_cast<BaseObject*> (object), Player::me());
				else
					dout(ERROR, NETWORK) << "Received NULL spawn object\n";
				return true;
			}
			case MSG_REQUEST_SPAWN: {
				if (!NetworkManager::instance().isServer()) {
					dout(ERROR, NETWORK) << "Received spawn request but I'm not server\n";
					return true;
				}
				// if listener knew of message origin, this data would be unnecessary
				NetworkID playerID = *( (NetworkID*) data);
				Player *player = (Player*) NetworkManager::instance().getObject(playerID);
				if (!player)
					dout(ERROR, NETWORK) << "Received NULL spawn player\n";
				else if (!scenario.valid())
					dout(ERROR, NETWORK) << "Cannot spawn player " << (player ? player->getName() : "NULL") << " without scenario\n";
				else
					scenario->spawn(player);
				return true;
			}
		}
		return false;
	}

	void ScenarioNetworkObjectListener::clear()
	{
		pendingObjects.clear();
		deletedObjects.clear();
	}

} // namespace
