#include "World.h"
#include "ode_osg.h"
#include "components/Geometry.h"
#include "components/Joint.h"
#include <mlog/Log.h>
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <moon/TaskTimer.h>
#include <osg/io_utils>

#ifdef _MSC_VER
#	pragma warning(disable:4800)
#endif

using namespace moon;
using namespace mlog;

namespace moodyn {
	
	const unsigned int _maxcontacts = 16;
    
	struct worldinfo {
		dWorldID world;
		dJointGroupID contactgroup;
	};
	
	struct FeedbackInfo {
		dJointFeedback fb;
		osg::observer_ptr<Geometry> geo1;
		osg::observer_ptr<Geometry> geo2;
		FeedbackInfo() : geo1(NULL), geo2(NULL) { 
			memset(&fb, 0, sizeof(dJointFeedback));
		}
	};
	
	typedef std::vector< FeedbackInfo* > FeedbackList;
	FeedbackList contactfeedback;
	
	typedef std::map< osg::observer_ptr<Geometry>, bool> feedbackresetMap;
	feedbackresetMap feedbackreset;
	
	void nearCallback (void *data, dGeomID o1, dGeomID o2)
	{
		moon::TaskTimer::ScopedTask task("Simulation/ODE/Collide/nearCallback");
		bool done = false;
		
		worldinfo *winfo = (worldinfo*) data;
		dWorldID world = winfo->world;
		dJointGroupID contactgroup = winfo->contactgroup;

		// Collide spaces first
		if (dGeomIsSpace (o1) || dGeomIsSpace (o2)) {
			// colliding a space with something
			dSpaceCollide2 (o1,o2,data,&nearCallback);
			// collide all geoms internal to the space(s)
			if (dGeomIsSpace (o1)) dSpaceCollide ((dSpaceID)o1,data,&nearCallback);
			if (dGeomIsSpace (o2)) dSpaceCollide ((dSpaceID)o2,data,&nearCallback);
			return;
		}
		
		//	if ((b1 || b2) && dAreConnectedExcluding (b1,b2,dJointTypeContact)) return;
		
		// Skip contact between two static geometries
		if (dGeomGetBody(o1) == NULL && dGeomGetBody(o2) == NULL)
			return;
		
		Geometry *geo1 = (Geometry*) dGeomGetData(o1);
		Geometry *geo2 = (Geometry*) dGeomGetData(o2);
		if (geo1 == NULL || geo2 == NULL) 
			throw DynamicsException("ODE Geom with no Geometry attached");
		
		// Skip contact between bodies that are connected with a joint (if specified for the Geometry)
		if (geo1->getBody() && geo2->getBody() && geo1->getBody()->isRealized() && geo2->getBody()->isRealized() 
			&& dAreConnectedExcluding(geo1->getBody()->id(), geo2->getBody()->id(), dJointTypeContact)
			&& (!geo1->shouldContactConnected() || !geo2->shouldContactConnected()))
			return;

		// Call "near" callback
		if (geo1->getNearCallback())
			done = !(*geo1->getNearCallback())(geo1,geo2);
		if (!done && geo2->getNearCallback())
			done = !(*geo2->getNearCallback())(geo2,geo1);
		if (done)
			return;
 
 		// Set contact parameters
		dContact thiscontact = World::instance().getContact(geo1->getMaterialID(),geo2->getMaterialID());
		// Multiply slip2 with velocity for tire sideways slip approximation
		if (thiscontact.surface.slip2 > 0) {
			osg::Vec3 v;
			if (geo1->getBody() && geo2->getBody())
				v = geo1->getBody()->getVelocity() - geo2->getBody()->getVelocity();
			else if (geo1->getBody())
				v = geo1->getBody()->getVelocity();
			else if (geo2->getBody())
				v = -geo2->getBody()->getVelocity();
			if (v.length() > 0.1 && geo1->getBody()) {
				thiscontact.surface.slip2 *= v.length();
				//osg::Vec3 gnorm = osgVec3FromOde(thiscontact.geom.normal);
				//dout(0) << "gnorm " << gnorm << " avel " << geo1->getBody()->getAngularVelocity() << "\n";
				//osg::Vec3 vn = gnorm ^ geo1->getBody()->getAngularVelocity();
				osg::Vec3 vn = geo1->getBody()->getAngularVelocity() ^ osg::Vec3(0,0,1);
				vn.normalize();
				// fdir1 should be the velocity in the "rolling direction" according to ODE manual
				thiscontact.fdir1[0] = vn.x();
				thiscontact.fdir1[1] = vn.y();
				thiscontact.fdir1[2] = vn.z();
				thiscontact.surface.mode |= dContactFDir1;
			} else
				thiscontact.surface.slip2 = 0;
		}
		dContact contact[_maxcontacts];

		//if (callUserFunctions(PRE_CONTACT))
		//    thiscontact = _contact;
		for (unsigned int i=0; i<_maxcontacts; i++) {
			contact[i] = thiscontact;
		}
		
		if (int numc = dCollide (o1,o2,_maxcontacts,&contact[0].geom,
								 sizeof(dContact))) {
			if (geo1->getContactCallback())
				done = !(*geo1->getContactCallback())(geo1,geo2);
			if (!done && geo2->getContactCallback())
				done = !(*geo2->getContactCallback())(geo2,geo1);
			
			// Default collision handler
			if (!done) {
				bool fbset =  false;
				for (int i=0; i<numc; i++) {
					// Skip contacts with depth 0, that tends to crash ODE
					if (contact[i].geom.depth < 1e-8) {
						//dout(WARN) << "Skipping contact with depth " << contact[i].geom.depth << "\n";
						continue;
					}
					dJointID cjoint = dJointCreateContact(world,contactgroup,&contact[i]);
					dJointAttach(cjoint, geo1->getBody() ? geo1->getBody()->id() : NULL, geo2->getBody() ? geo2->getBody()->id() : NULL);
					if (!fbset) {
						bool g1fb = geo1->wantsContactFeedback();
						bool g2fb = geo2->wantsContactFeedback();
						if (g1fb || g2fb) {
							FeedbackInfo* fbi = new FeedbackInfo;
							dJointSetFeedback(cjoint,&fbi->fb);
							fbi->geo1 = geo1;
							fbi->geo2 = geo2;
							contactfeedback.insert(contactfeedback.begin(), fbi);
							fbset = true; // feedback is only needed for one of the contacts
						}
					}
				}
			}
			
		}	
	}
	
	void World::parseXML(const TiXmlElement *element)
	{
		//=== DynamicsConfiguration
		dout(4) << "Dynamics configuration\n";
		//=* attribute: stepper="accurate|quick" (default quick)
		std::string str;
		if (XMLParser::parseStringAttribute(str, element, "stepper")) {
			if (str == "accurate")
				setStepper(ACCURATE);
			else if (str == "quick")
				setStepper(QUICK);
			else
				throw ParseException("Invalid 'stepper' specification", element);
		}
		//=* element: gravity value="(vector3)" [meter/second^2]
		setGravity(XMLParser::parseVector3(element,"gravity","meter/second^2",true,osg::Vec3(0,0,-9.81f)));
		//=* element: cfm value="(number)"
		//=. Constraint force mixing. See the ODE manual.
		dWorldSetCFM(worldID, XMLParser::parseDouble(element,"cfm","",true, dWorldGetCFM(worldID)));
		//=* element: erp value="(number)"
		//=. See the ODE manual.
		dWorldSetERP(worldID, XMLParser::parseDouble(element,"erp","",true, dWorldGetERP(worldID)));
		//=* element: autodisable value="true|false"
		//=. Set wether to use the auto disable feature for rigid bodies.
		dWorldSetAutoDisableFlag(worldID, (int)XMLParser::parseBoolean(element,"autodisable",true, dWorldGetAutoDisableFlag(worldID)));
		//=* element: autodisable_linear value="(number)" [meter/second]
		//=. Linear velocity threshold for auto disabling bodies.
		dWorldSetAutoDisableLinearThreshold(worldID, XMLParser::parseDouble(element,"autodisable_linear","meter/second",true, dWorldGetAutoDisableLinearThreshold(worldID)));
		//=* element: autodisable_angular value="(number)" [radian/second]
		//=. Angular velocity threshold for auto disabling bodies.
		dWorldSetAutoDisableAngularThreshold(worldID, XMLParser::parseDouble(element,"autodisable_angular","radian/second",true, dWorldGetAutoDisableAngularThreshold(worldID)));
		//=* element: autodisable_steps value="(number)"
		//=. Minimum number of simulation steps for auto disabling bodies.
		dWorldSetAutoDisableSteps(worldID, XMLParser::parseInt(element,"autodisable_steps","",true, dWorldGetAutoDisableSteps(worldID)));
		//=* element: autodisable_steps value="(number)" [second]
		//=. Minimum simulation time steps for auto disabling bodies.
		dWorldSetAutoDisableTime(worldID,XMLParser::parseDouble(element,"autodisable_time","second",true, dWorldGetAutoDisableTime(worldID)));
		//=* element: maxcorrectingvel value="(number)" [meter/second]
		//=. Maximum correcting velocity for contact joints.
		dWorldSetContactMaxCorrectingVel(worldID,XMLParser::parseDouble(element,"maxcorrectingvel","meter/second",true, dWorldGetContactMaxCorrectingVel(worldID)));
		//=* element: contactsurfacelayer value="(number)" [meter]
		dWorldSetContactSurfaceLayer(worldID,XMLParser::parseDouble(element,"contactsurfacelayer","meter",true, dWorldGetContactSurfaceLayer(worldID)));

		//=* element: contacts
		const TiXmlElement *contactsElement = element->FirstChildElement("contacts");
		if (contactsElement) {
			for (const TiXmlElement *celement = contactsElement->FirstChildElement(); celement; celement = celement->NextSiblingElement()) {
				unsigned int mat1, mat2;
				//=** element: default
				if (std::string(celement->Value()) == "default")
					mat1 = mat2 = 0;
				//=** repeatable element: contact material1="(name)" material2="(name)"
				//=. Specification of contact joint properties for contact between two materials
				else if (std::string(celement->Value()) != "contact")
					throw ParseException("Expected 'contact' element in 'contacts' group", celement);
				else {
					std::string mat1str = XMLParser::parseStringAttribute(celement, "material1");
					std::string mat2str = XMLParser::parseStringAttribute(celement, "material2", true, "default");
					dout(5) << "  Contact between materials " << mat1str << " and " << mat2str << "\n";
					mat1 = getOrCreateMaterialID(mat1str);
					mat2 = getOrCreateMaterialID(mat2str);
				}
				dContact contact;
				memset(&contact, 0, sizeof(dContact));
				//=*** element: mu value="(number)|infinity" (required)
				contact.surface.mode = 0;
				if (XMLParser::parseString(celement,"mu") == "infinity")
					contact.surface.mu = dInfinity;
				else
					contact.surface.mu = XMLParser::parseDouble(celement,"mu");
				//=*** element: mu2 value="(number)|infinity" (default="0")
				if (XMLParser::parseString(celement,"mu2",true,"") == "infinity")
					contact.surface.mu2 = dInfinity;
				else
					contact.surface.mu2 = XMLParser::parseDouble(celement,"mu2","",true,0);
				if (contact.surface.mu2)
					contact.surface.mode |= dContactMu2;
				//=*** element: bounce value="(number)" (default="0")
				contact.surface.bounce = XMLParser::parseDouble(celement,"bounce","",true,0);
				if (contact.surface.bounce)
					contact.surface.mode |= dContactBounce;
				//=*** element: soft_erp value="(number)" (default="0")
				contact.surface.soft_erp = XMLParser::parseDouble(celement,"soft_erp","",true,0);
				if (contact.surface.soft_erp)
					contact.surface.mode |= dContactSoftERP;
				//=*** element: soft_cfm value="(number)" (default="0")
				contact.surface.soft_cfm = XMLParser::parseDouble(celement,"soft_cfm","",true,0);
				if (contact.surface.soft_cfm)
					contact.surface.mode |= dContactSoftCFM;
				//=*** element: slip1 value="(number)" (default="0")
				contact.surface.slip1 = XMLParser::parseDouble(celement,"slip1","",true,0);
				if (contact.surface.slip1)
					contact.surface.mode |= dContactSlip1;
				//=*** element: slip2 value="(number)" (default="0")
				contact.surface.slip2 = XMLParser::parseDouble(celement,"slip2","",true,0);
				if (contact.surface.slip2)
					contact.surface.mode |= dContactSlip2;
				//=*** element: approx1_1 value="true|false"
				if (XMLParser::parseBoolean(celement,"approx1_1",true,false))
					contact.surface.mode |= dContactApprox1_1;
				//=*** element: approx1_2 value="true|false"
				if (XMLParser::parseBoolean(celement,"approx1_2",true,false))
					contact.surface.mode |= dContactApprox1_2;
				//=*** element: approx1 value="true|false"
				if (XMLParser::parseBoolean(celement,"approx1",true,false))
					contact.surface.mode |= dContactApprox1;
				setContact(mat1,mat2,contact);
			}
		}
		//=* element: refmass value="(number)" [kg]
		referenceMass = XMLParser::parseDouble(element, "refmass", "kg", true, referenceMass);
	}
	
	void World::writeXML(TiXmlElement *element) const
	{
		/// \todo Implement
	}
	
	void World::setGravity(const osg::Vec3& gravity)
	{ 
		dWorldSetGravity(worldID, gravity.x(), gravity.y(), gravity.z());
	}
	
	osg::Vec3 World::getGravity()
	{
		dVector3 g;
		dWorldGetGravity(worldID, g);
		return osg::Vec3(g[0], g[1], g[2]);
	}
	
	void World::setStepper(const Stepper newstepper) { stepper = newstepper; }
	World::Stepper World::getStepper() { return stepper; }
	
	dContact& World::getContact(const unsigned int material_id1, const unsigned int material_id2)
	{
		if (material_id1 > 255 || material_id2 > 255)
			throw DynamicsException("Maximum number of materials (255) exceeded");
		unsigned int contact_id;
		if (material_id1 > material_id2)
			contact_id = (material_id2 << 8) | material_id1;
		else
			contact_id = (material_id1 << 8) | material_id2;
		// Primarily use contact parameters specified for the combination of two materials
		if (contacts.find(contact_id) != contacts.end())
			return contacts[contact_id];
		// Use contact parameters for one material with default material if available
		else if (contacts.find(material_id1) != contacts.end())
			return contacts[material_id1];
		else if (contacts.find(material_id2) != contacts.end())
			return contacts[material_id2];
		// Last resort - use default contact parameters
		return contacts[0];
	}
	
	void World::setContact(const unsigned int material_id1, const unsigned int material_id2, dContact& contact)
	{
		if (material_id1 > 255 || material_id2 > 255)
			throw DynamicsException("Maximum number of materials (255) exceeded");
		unsigned int contact_id;
		if (material_id1 > material_id2)
			contact_id = (material_id2 << 8) | material_id1;
		else
			contact_id = (material_id1 << 8) | material_id2;
		contacts[contact_id] = contact;
	}
	
	const unsigned int World::getMaterialID(const std::string& name)
	{
		if (name == "default")
			return 0;
		if (materials.find(name) != materials.end())
			return materials[name];
		throw DynamicsException(std::string("Unknown material: ") + name);
	}
	
	const unsigned int World::getOrCreateMaterialID(const std::string& name)
	{
		if (name == "default")
			return 0;
		if (materials.find(name) != materials.end())
			return materials[name];
		unsigned int maxid = 0;
		for (MaterialTable::iterator i = materials.begin(); i != materials.end(); i++) {
			if (i->second > maxid)
				maxid = i->second;
		}
		materials[name] = maxid + 1;
		return maxid + 1;
	}
	
	void World::update(const double dt)
	{
		moon::TaskTimer::ScopedTask task("Simulation/ODE");
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(mutex);

		// find collisions and add contact joints
		worldinfo winfo;
		winfo.world = worldID;
		winfo.contactgroup = contactGroup;

		feedbackreset.clear();
		for (FeedbackList::iterator it = contactfeedback.begin(); it != contactfeedback.end(); it++) {
			FeedbackInfo* fbi = *it;
			feedbackreset[fbi->geo1.get()] = true;
			feedbackreset[fbi->geo2.get()] = true;
			delete *it;
		}
		contactfeedback.clear();

		// collide geometries
		{
			moon::TaskTimer::ScopedTask collidetask("Simulation/ODE/Collide");			
			dSpaceCollide(defaultSpace, &winfo,&nearCallback);
		}

		// step world
		{
			moon::TaskTimer::ScopedTask steptask("Simulation/ODE/Step");
			switch (stepper) {
				case QUICK:
					dWorldQuickStep(worldID, dt);
					break;
				case ACCURATE:
					dWorldStep(worldID, dt);
					break;
			}
		}

		// remove all contact joints
		dJointGroupEmpty(contactGroup);
		
		{
			moon::TaskTimer::ScopedTask feedbacktask("Simulation/ODE/Feedback");
	
			// distribute contact feedbacks to geometries
			for (std::size_t i = 0; i < contactfeedback.size(); i++) {
				FeedbackInfo* fbi = contactfeedback[i];
				if (fbi->geo1.valid()) {
					fbi->geo1->setContactForce(osg::Vec3(fbi->fb.f1[0], fbi->fb.f1[1], fbi->fb.f1[2])*referenceMass);
					fbi->geo1->setContactTorque(osg::Vec3(fbi->fb.t1[0], fbi->fb.t1[1], fbi->fb.t1[2])*referenceMass);
					feedbackreset[fbi->geo1.get()] = false;
				}
				if (fbi->geo2.valid()) {
					fbi->geo2->setContactForce(osg::Vec3(fbi->fb.f2[0], fbi->fb.f2[1], fbi->fb.f2[2])*referenceMass);
					fbi->geo2->setContactTorque(osg::Vec3(fbi->fb.t2[0], fbi->fb.t2[1], fbi->fb.t2[2])*referenceMass);
					feedbackreset[fbi->geo2.get()] = false;
				}
				if (fbi->geo1.valid() && fbi->geo1->getContactFeedbackCallback()) {
					(*fbi->geo1->getContactFeedbackCallback())(fbi->geo1.get(),fbi->geo2.get());
					feedbackreset[fbi->geo1.get()] = false;
				}
				if (fbi->geo2.valid() && fbi->geo2->getContactFeedbackCallback()) {
					(*fbi->geo2->getContactFeedbackCallback())(fbi->geo2.get(),fbi->geo1.get());
					feedbackreset[fbi->geo2.get()] = false;
				}
			}
	
			for (feedbackresetMap::iterator it = feedbackreset.begin(); it != feedbackreset.end(); it++) {
				if (it->second) {
					if (!it->first.valid())
						continue;
					Geometry *geo = it->first.get();
					geo->setContactForce(osg::Vec3(0,0,0));
					geo->setContactTorque(osg::Vec3(0,0,0));
					if (geo->getContactFeedbackCallback())
						(*geo->getContactFeedbackCallback())(it->first.get(), NULL);
				}
			}
			
		}
	}
		
	dWorldID World::id() { return worldID; }
	dSpaceID World::getDefaultSpace() const { return defaultSpace; }	
	dJointGroupID World::getContactGroup() { return contactGroup; }
	
	World& World::instance()
	{
		if (!instancePtr)
			instancePtr = new World;
		return *instancePtr;
	}
	
	World::World()
	:	SimulationListener(),
		stepper(QUICK),
		referenceMass(1.f)
	{
		mlog::dout(1) << "Initializing ODE\n";
		dInitODE();
		worldID = dWorldCreate();
		defaultSpace = dSimpleSpaceCreate(0);
		//defaultSpace = dHashSpaceCreate(0);
		contactGroup = dJointGroupCreate(0);
		// Setup some defaults
		dWorldSetGravity(worldID, 0, 0, -9.81f);
		dWorldSetAutoDisableFlag(worldID, true);
		dWorldSetAutoDisableLinearThreshold(worldID, 0.1f);
		dWorldSetAutoDisableAngularThreshold(worldID, 0.1f);
		// Setup default contact
		dContact defaultcontact;
		defaultcontact.surface.mode = dContactBounce | dContactSoftCFM;
	    defaultcontact.surface.mu = dInfinity;
	    defaultcontact.surface.bounce = 0.8f;
	    defaultcontact.surface.bounce_vel = 1;
	    defaultcontact.surface.soft_cfm = 0.001f;
		contacts[0] = defaultcontact;
		// Set default tessellation hints for drawing geom and joint visuals
		hints = new osg::TessellationHints;
		hints->setCreateBackFace(false);
		hints->setCreateTextureCoords(false);
		hints->setCreateNormals(false);
		hints->setDetailRatio(0.5);
		Geometry::default_hints = hints.get();
		Joint::default_hints = hints.get();
	}
	
	World::~World()
	{
		dWorldDestroy(worldID);
	}
	
	World* World::instancePtr = NULL;
	OpenThreads::Mutex World::mutex;
	
	REGISTER_Object_Alias(moodyn, DynamicsConfiguration, DynamicsConfiguration);
	
	DynamicsConfiguration::DynamicsConfiguration()
	:	FactoryProduct()
	{
	}
	
	DynamicsConfiguration::DynamicsConfiguration(const DynamicsConfiguration& source, const osg::CopyOp& copyop)
	:	FactoryProduct(source, copyop)
	{
		mlog::dout(WARN) << "Copying dynamics configuration is not implemented\n";
	}
	
	void DynamicsConfiguration::parseXML(const TiXmlElement *element)
	{
		World::instance().parseXML(element);
	}
	
	void DynamicsConfiguration::writeXML(TiXmlElement *element) const
	{
		mlog::dout(WARN) << "Writing dynamics configuration is not implemented\n";
	}

} // namespace
