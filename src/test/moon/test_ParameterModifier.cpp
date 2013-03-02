#include <unittest++/UnitTest++.h>
#include <moon/Parameter.h>
#include <moon/Modifier.h>
#include <moon/objects/BaseObject.h>

TEST (ParameterModifierConnection) {
	moon::Parameter param;
	moon::Modifier mod, mod2;
	CHECK(!param.isConnected());
	mod.setParameter(&param);
	CHECK(param.isConnected());
	mod2.setParameter(&param);
	mod.setParameter(NULL);
	CHECK(param.isConnected());
	mod2.setParameter(NULL);
	CHECK(!param.isConnected());
}

TEST (ParameterModifierValues) {
	moon::Parameter param;
	moon::Modifier mod, mod2;
	mod2.setRatio(3);
	mod2.setOffset(5);
	// Set a default value
	mod.set(10);
	mod2.set(10);
	param.set(100);
	CHECK_CLOSE(10, mod.get(), 1e-5);
	CHECK_CLOSE(35, mod2.get(), 1e-5);
	// Connect to parameter
	mod.setParameter(&param);
	mod2.setParameter(&param);
	CHECK_CLOSE(100, mod.get(), 1e-5);
	CHECK_CLOSE(305, mod2.get(), 1e-5);
}

TEST (ParametersInObjectHierarchy) {
	osg::ref_ptr<moon::BaseObject> object = new moon::BaseObject;
	std::string paramname = object->getParameter(0)->getName();
	CHECK_EQUAL(object->getParameter(0), object->getParameter(paramname));
	
	osg::ref_ptr<moon::BaseObject> child = new moon::BaseObject, child2 = new moon::BaseObject;
	child->setName("child");
	child2->setName("child2");
	object->addChild(child.get());
	object->addChild(child2.get());
	object->initialize();
	
	// Check different ways to access parameters - all parameters should be accessible from all objects in the hierarchy
	CHECK_EQUAL(object->getParameter(0), child->findParameter("root " + paramname));
	CHECK_EQUAL(child->getParameter(0), object->findParameter(child->getName() + " " + paramname));
	CHECK_EQUAL(child2->getParameter(0), object->findParameter(child2->getName() + " " + paramname));
	CHECK_EQUAL(child->getParameter(0), child2->findParameter(child->getName() + " " + paramname));
}
