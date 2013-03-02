#ifndef MOON_SCENARIO_H
#define MOON_SCENARIO_H

#include "Export.h"
#include "objects/TransformObject.h"
#include "FactoryProduct.h"
#include "ObjectFactory.h"
#include "objects/BaseObject.h"
#include "objects/Camera.h"
#include "components/Script.h"
#include "Environment.h"
#include "SimulationManager.h"
#include <moonet/NetworkObject.h>
#include <moonet/NetworkListener.h>
#include <osg/Group>
#include <osgGA/CameraManipulator>
#include <vector>
#include <map>

namespace moon {

	/// \addtogroup core
	/// @{

	/// Container for objects and parameters associated with a simulation scenario, or game level
	class MOON_EXPORT Scenario : public ComponentContainer, public SimulationListener {
	public:
		Scenario();
		Scenario(const Scenario& scenario, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
		META_Object(moon, Scenario);

		virtual void parseXML(const TiXmlElement *element);
		virtual void writeXML(TiXmlElement *element) const;

		virtual void initialize();
		/// Reset states of all objects in the scenario
		virtual void reset();
		/// Realize (setup geometry etc) all objects in the scenario
		virtual void realize();
		/// Unrealize all objects in the scenario
		virtual void unrealize();
		/// Update simulation of all objects in the scenario
		virtual void update(const double dt = 0);

		/// Get the root node for visual objects
		osg::Group* getRootNode();

		/// Add an object to the scenario
		virtual void addComponent(Component *component, const bool construct, moonet::Client *owner = NULL);
		/// Add an object to the scenario
		virtual void addComponent(Component *component);
		/// Remove an object from the scenario
		virtual void removeComponent(Component *component);
		/// Get the camera that should be activated when the scenario is loaded
		Camera* getFirstCamera() { return firstCamera.get(); }
		/// Get the Environment in this scenario
		Environment* getEnvironment() { return environment.get(); }
		/// Set the Environment for this scenario
		void setEnvironment(Environment *env);
		/// Set display mode for all objects
		void setDisplayMode(const unsigned int mode);
		/// Get display mode
		unsigned int getDisplayMode() const { return displayMode; }

		void spawn(moonet::Player *player);
		void activateSpawnObject(BaseObject *object, moonet::Player *player);
		void releaseSpawnObject(moonet::Player *player);

		void removeRemoteObjects();

                unsigned int getManipulator() const { return manipulator; }
                const osg::Matrixd& getViewMatrix() const { return viewMatrix; }

		/// Get current scenario (set when realize() is called)
		static Scenario* current() { return currentScenario.get(); }

	protected:
		virtual ~Scenario();

	private:
		osg::ref_ptr<osg::Group> rootnode;
		osg::observer_ptr<osg::Group> shadowGroup;

		//ObjectFactory::ObjectList objects;
		typedef std::vector< osg::observer_ptr<BaseObject> > BaseObjectList;
		BaseObjectList baseObjects;
		typedef std::vector< osg::ref_ptr<BaseObject> > SpawnObjectList;
		SpawnObjectList spawnObjects;
		typedef std::map< moonet::Player*, osg::ref_ptr<BaseObject> > SpawnObjectMap;
		SpawnObjectMap allocatedSpawnObjects;
		typedef std::map< moonet::Player*, osg::observer_ptr<BaseObject> > SpawnObjectObserverMap;
		SpawnObjectObserverMap activeSpawnObjects;
		osg::observer_ptr<Camera> firstCamera;
		osg::ref_ptr<Environment> environment;
		bool realized;
		unsigned int displayMode;

		enum NetworkMode { UNKNOWN, SERVER, CLIENT, SERVER_ONLY, CLIENT_ONLY, COMMON, STANDALONE, SPAWN_INSTANCE };
		typedef std::map< FactoryProduct*, NetworkMode > NetworkModeMap;
		NetworkModeMap networkMode;

		osg::ref_ptr<Script> resetScript, realizeScript, unrealizeScript;
                unsigned int manipulator;
                osg::Matrixd viewMatrix;

                static osg::observer_ptr<Scenario> currentScenario;
	};

	/// A network listener that adds/removes network objects to/from the scenario
	class MOON_EXPORT ScenarioNetworkObjectListener : public moonet::NetworkListener {
	public:
		void setScenario(Scenario *scenario);
		virtual void onNewObject(moonet::NetworkObject *object);
		virtual void onDeleteObject(moonet::NetworkObject *object);
		virtual void onPlayerGone(moonet::Player *player);
		virtual void onDownloadComplete();
		virtual bool onMessage(const short id, const char *data, const short len, const bool broadcast);

		void clear();

		virtual ~ScenarioNetworkObjectListener() {}
	protected:
		osg::observer_ptr<Scenario> scenario;
		typedef std::vector< moonet::NetworkObject* > ObjectList;
		ObjectList pendingObjects;
		ObjectFactory::ObjectList deletedObjects;
	};

	/// @}
}

#endif
