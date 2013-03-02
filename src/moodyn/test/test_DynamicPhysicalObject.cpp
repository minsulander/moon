#include <unittest++/UnitTest++.h>
#include <moodyn/objects/DynamicPhysicalObject.h>
#include <moon/Scenario.h>
#include <mlog/Log.h>
#include <moodyn/World.h>
#include <osg/io_utils>

using namespace moon;
using namespace moodyn;

TEST (DynamicPhysicalObject_Gravity) {
	osg::ref_ptr<DynamicPhysicalObject> object = new DynamicPhysicalObject;
	object->addComponent(new Body);
	object->initialize();
	
	object->setPosition(0,0,9.81);
	CHECK_ARRAY_CLOSE(osg::Vec3(0, 0, 9.81), object->getPosition(), 3, 1e-5);
	object->getBody()->setMass(1);
	CHECK_CLOSE(1, object->getBody()->getMass(), 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,9.81), object->getPosition(), 3, 1e-5);
	
	object->realize();
	
	const double dt = 0.01;
	for (double t = 0; t < 1.0; t += dt) {
		SimulationManager::instance().update(dt);
		object->update(dt);
	}
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,9.81/2.0), object->getPosition(), 3, 0.5);
}

TEST (DynamicPhysicalObject_FallOnPlane) {
	// Make a rigid body with a box
	osg::ref_ptr<DynamicPhysicalObject> object = new DynamicPhysicalObject;
	object->addComponent(new Body);
	object->initialize();
	
	object->setPosition(0,0,10);
	object->getBody()->setMass(1);
	osg::ref_ptr<Geometry> geo = new Geometry;
	geo->addShape(Geometry::BOX, 1, 1, 1);
	object->setGeometry(geo.get());

	osg::ref_ptr<Geometry> plane = new Geometry;
	plane->addShape(Geometry::PLANE, 0, 0, 1, 0);
	
	object->realize();
	plane->realize();
	
	// Make sure everything has been realized
	CHECK(geo->isRealized());
	CHECK(object->getBody()->isRealized());

	// Make sure everyone has the same idea of the position..
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,10), object->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(object->getPosition(), object->getBody()->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(object->getPosition(), object->getGeometry()->getPosition(), 3, 1e-5);

	// ..also after 1 second of simulation
	SimulationManager::instance().update(1.0);
	object->update(1.0);
	CHECK_ARRAY_CLOSE(object->getPosition(), object->getBody()->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(object->getPosition(), object->getGeometry()->getPosition(), 3, 1e-5);

	// See if the plane was in the way of the box
	SimulationManager::instance().update(100.0);
	object->update(100.0);
	CHECK_CLOSE(0.5, object->getPosition().z(), 0.1);
	CHECK_ARRAY_CLOSE(object->getPosition(), object->getBody()->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(object->getPosition(), object->getGeometry()->getPosition(), 3, 1e-5);
	
	// Remove the plane and see that it falls again
	plane = NULL;
	object->getBody()->enable();
	SimulationManager::instance().update(10.0);
	object->update(10.0);
	CHECK(object->getPosition().z() < 0.0);
}

TEST (DynamicPhysicalObject_WithChildren) {
	osg::ref_ptr<DynamicPhysicalObject> parent = new DynamicPhysicalObject;
	parent->addComponent(new Body);
	osg::ref_ptr<DynamicPhysicalObject> child = new DynamicPhysicalObject;
	child->addComponent(new Body);
	parent->addChild(child.get());
	// We need a scenario for its root node
	osg::ref_ptr<Scenario> scenario = new Scenario;
	scenario->addComponent(parent.get());
	
	CHECK_EQUAL(1u, parent->getNumChildren());
	CHECK_EQUAL(parent.get(), child->getParent());
	CHECK_EQUAL(child.get(), parent->getChild(0));
	
	// Check that the transformation methods produce the expected results
	parent->setPosition(0,0,5);
	child->setPosition(1,1,0);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,5), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);
	
	parent->setPosition(5,5,10);
	CHECK_ARRAY_CLOSE(osg::Vec3(6,6,10), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);

	// Realize the objects (i.e. create the body and stuff) - this
	// makes the child object rearrange transforms so that the transform
	// is not a child of the parent transform... all because ODE only handles
	// world coordinates, and that in combination with KinematicObject doing its
	// fancy extrapolation made things very difficult if I were to maintain the
	// normal transform relationship.
	
	parent->realize();
	CHECK(child->isRealized());
	CHECK_EQUAL(parent->getTransform()->getParent(0), child->getTransform()->getParent(0));
	
	// Check that the transformation methods still produce the same results	
	CHECK_ARRAY_CLOSE(osg::Vec3(6,6,10), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);
	
	parent->setPosition(0,10,5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,11,5), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);
	
	// Unrealize again and make sure things go back to "normal"
	parent->unrealize();
	CHECK(!child->isRealized());
	CHECK_EQUAL(parent->getTransform(), child->getTransform()->getParent(0));
	CHECK_ARRAY_CLOSE(osg::Vec3(1,11,5), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);
}

TEST (DynamicPhysicalObject_Reset) {
	osg::ref_ptr<DynamicPhysicalObject> parent = new DynamicPhysicalObject;
	parent->addComponent(new Body);
	parent->setName("parent");
	osg::ref_ptr<DynamicPhysicalObject> child = new DynamicPhysicalObject;
	child->addComponent(new Body);
	child->setName("child");
	parent->addChild(child.get());
	osg::ref_ptr<Scenario> scenario = new Scenario;
	scenario->addComponent(parent.get());
	
	World::instance().setGravity(osg::Vec3(0,0,0));

	child->setPosition(1,1,0);
	parent->setPosition(5,5,10);
	parent->setVelocity(osg::Vec3(-10,0,0));
	child->setVelocity(osg::Vec3(10,0,0));
	// child world velocity is 0
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,0), child->getWorldVelocity(), 3, 1e-5);
	
	parent->setResetState();
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);

	parent->reset();
	// The objects shouldn't have moved
	CHECK_ARRAY_CLOSE(osg::Vec3(5,5,10), parent->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(6,6,10), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);

	parent->realize();
	SimulationManager::instance().update(10.0);
	parent->update(10.0);
	// Now they should have moved
	CHECK_ARRAY_CLOSE(osg::Vec3(-95,5,10), parent->getPosition(), 3, 0.1);
	CHECK((osg::Vec3(5,5,10) - parent->getPosition()).length() > 0.1);
	CHECK((osg::Vec3(1,1,0) - child->getPosition()).length() > 0.1);
	// child position doesn't change as its world velocity is 0
	CHECK((osg::Vec3(6,6,10) - child->getWorldTransformMatrix().getTrans()).length() < 0.1);
	
	// Set position and velocity to something completely different
	parent->setPosition(20,10,5);
	child->setPosition(0,5,91);
	parent->setVelocity(osg::Vec3(1,2,3));
	child->setVelocity(osg::Vec3(3,2,1));
	
	// Reset
	parent->reset();
	parent->realize();
	//parent->setVelocity(osg::Vec3(-10,0,0));
	//child->setVelocity(osg::Vec3(10,0,0));
	// Check that positions have been reset
	CHECK_ARRAY_CLOSE(osg::Vec3(5,5,10), parent->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(6,6,10), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);

	SimulationManager::instance().update(10.0);
	parent->update(10.0);
	// Check that velocities have been reset correctly
	CHECK_ARRAY_CLOSE(osg::Vec3(-95,5,10), parent->getPosition(), 3, 0.1);
	CHECK((osg::Vec3(1,1,0) - child->getPosition()).length() > 0.1);
	
	// Resetting only the child should move it to its location relative its parent
	child->reset();
	CHECK((osg::Vec3(5,5,10) - parent->getPosition()).length() > 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,1,0), child->getPosition(), 3, 1e-5);
	
}

TEST (DynamicPhysicalObject_Velocities) {
	osg::ref_ptr<DynamicPhysicalObject> parent = new DynamicPhysicalObject;
	parent->addComponent(new Body);
	parent->setName("parent");
	osg::ref_ptr<DynamicPhysicalObject> child = new DynamicPhysicalObject;
	child->addComponent(new Body);
	child->setName("child");
	parent->addChild(child.get());
	osg::ref_ptr<Scenario> scenario = new Scenario;
	scenario->addComponent(parent.get());

	World::instance().setGravity(osg::Vec3(0,0,-9.81));

	parent->setAttitude(M_PI/2.0, 0, 0);
	child->setAttitude(-M_PI/2.0, 0, 0);
	
	// Set a velocity in parent coordinate frame
	child->setVelocity(osg::Vec3(1,2,0));
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,0), child->getVelocity(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(2,-1,0), child->getVelocity(true), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(2,-1,0), child->getWorldVelocity(), 3, 1e-5);
	
	// Realize and check it's the same
	parent->realize();
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,0), child->getVelocity(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(2,-1,0), child->getVelocity(true), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(2,-1,0), child->getWorldVelocity(), 3, 1e-5);
	// Double-check transform
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PI/2.0, 0, 0), parent->getAttitude(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PI*3.0/2.0, 0, 0), child->getAttitude(), 3, 1e-5);
	
	// Run simulation and check position in parent and world coordinate frame
	SimulationManager::instance().update(1.0);
	parent->update(1.0);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,0), child->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(2,-1,0), child->getWorldTransformMatrix().getTrans(), 2, 1e-5); // note the 2! only x,y checked

	// Double check velocity (and gravity while we're at it 9.81 m/s^2 for one second = 9.81 m/s
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,0), child->getVelocity(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,-9.81), parent->getVelocity(), 3, 1e-5);
	
	child->setVelocity(osg::Vec3(3,7,1), false);
	SimulationManager::instance().update(1.0);
	parent->update(1.0);
	CHECK_ARRAY_CLOSE(osg::Vec3(3,7,1), child->getVelocity(false), 3, 1e-5);
}
