#include <unittest++/UnitTest++.h>
#include <moon/objects/KinematicObject.h>
#include <cmath>
#include <osgUtil/UpdateVisitor>

using namespace moon;

struct KinematicObjectFixture
{
	KinematicObjectFixture() {
		object = new KinematicObject;
		framestamp = new osg::FrameStamp;
	}

	osg::ref_ptr<KinematicObject> object;
	osg::ref_ptr<osg::FrameStamp> framestamp;

	void updateNode(osg::Node *node, const double dt) {
		// Do update traversal but no rendering
		framestamp->setReferenceTime(framestamp->getReferenceTime() + dt);
		framestamp->setSimulationTime(framestamp->getSimulationTime() + dt);
		framestamp->setFrameNumber(framestamp->getFrameNumber()+1);
		osgUtil::UpdateVisitor updateVisitor;
		updateVisitor.setFrameStamp(framestamp.get());
		node->accept(updateVisitor);
	}
};

TEST_FIXTURE (KinematicObjectFixture, KinematicObject) {
	object->setAttitude(0, M_PI/2.0, 0);
	// Velocity specified in relative (body) coordinates 
	object->setVelocity(osg::Vec3(0, 1, 0), true);
	CHECK_ARRAY_CLOSE(osg::Vec3(0, 0, 1), object->getVelocity(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(0, 1, 0), object->getVelocity(true), 3, 1e-5);
	// Velocity specified in absolute (earth) coordinates
	object->setVelocity(osg::Vec3(0, 0, 1));
	CHECK_ARRAY_CLOSE(osg::Vec3(0, 1, 0), object->getVelocity(true), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(0, 0, 1), object->getVelocity(), 3, 1e-5);
}

TEST_FIXTURE (KinematicObjectFixture, KinematicObjectMovement) {
	// First update needed to set timestamp
	updateNode(object->getTransform(), 0.1);
	// Set a linear velocity
	object->setVelocity(osg::Vec3(0,10,0));
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,10,0), object->getPosition(), 3, 0.01);
	// Set a linear velocity in body coordinates
	object->setAttitude(M_PI/2.0,M_PI/6.0,0.0);
	object->setVelocity(osg::Vec3(0,10,0), true);
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(10.0*cos(M_PI/6.0), 10.0, 10.0*sin(M_PI/6.0)), object->getPosition(), 3, 0.01);
	
	// Set angular velocities
	object->setPosition(0,0,0);
	object->setVelocity(0,0,0);
	
	// Heading change
	object->setAttitude(0,0,0);
	object->setAngularVelocity(0, 0, 3.0*M_PI/2.0);
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PI/2.0, 0, 0), object->getAttitude(), 3, 0.01);
	
	// Pitch
	object->setAttitude(0,0,0);
	object->setAngularVelocity(M_PI/4.0, 0, 0);
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(0, M_PI/4.0, 0), object->getAttitude(), 3, 0.01);
	
	// Roll
	object->setAttitude(0,0,0);
	object->setAngularVelocity(0, M_PI/3.0, 0);
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(0, 0, M_PI/3.0), object->getAttitude(), 3, 0.01);
	
}

TEST_FIXTURE (KinematicObjectFixture, KinematicObjectAnimation) {
	// Create an animation path
	osg::AnimationPath *anim = new osg::AnimationPath;
	anim->insert(0, osg::AnimationPath::ControlPoint(osg::Vec3(0,10,0)));
	anim->insert(1, osg::AnimationPath::ControlPoint(osg::Vec3(-10,0,0)));
	anim->setLoopMode(osg::AnimationPath::SWING);
	object->setAnimationPath(anim);
	
	// Set base position
	object->setPosition(5,5,5);
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_CLOSE(1.0, object->getAnimationTime(), 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(-5,-5,5), object->getPosition(), 3, 0.01);
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(5,5,5), object->getPosition(), 3, 0.01);
	
	// Move to a different base position
	object->setPosition(0,-5,15);
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(-10,-15,15), object->getPosition(), 3, 0.01);
}

TEST_FIXTURE (KinematicObjectFixture, KinematicObjectReset) {
	object->setPosition(1,2,3);
	object->setResetState();
	// First update needed to set timestamp
	updateNode(object->getTransform(), 0.1);
	// Set a linear velocity
	object->setVelocity(osg::Vec3(0,10,0));
	for (double t = 0.1; t < 1; t += 0.1)
		updateNode(object->getTransform(), 0.1);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,12,3), object->getPosition(), 3, 0.01);
	
	object->reset();
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,3), object->getPosition(), 3, 0.01);
}

TEST (KinematicObjectWorldVelocity) {
	osg::ref_ptr<KinematicObject> parent, child, child2;
	parent = new KinematicObject;
	child = new KinematicObject;
	child2 = new KinematicObject;
	parent->addChild(child.get());
	child->addChild(child2.get());
	child->setPosition(1,0,0);
	child2->setPosition(0,2,0);
	child->setAttitude(M_PI/2,0,0);
	child->setVelocity(-2,0,0,true);
	parent->setVelocity(0,3,0);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,3,0), parent->getWorldVelocity(), 3, 0.01);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,5,0), child->getWorldVelocity(), 3, 0.01);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,5,0), child2->getWorldVelocity(), 3, 0.01);
	
	parent->setAngularVelocity(0,0,2);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,7,0), child->getWorldVelocity(), 3, 0.01);
	/// \todo Proper handling of world velocity and angular velocities...
	//CHECK_ARRAY_CLOSE(osg::Vec3(0,10,0), child2->getWorldVelocity(), 3, 0.01);
}

