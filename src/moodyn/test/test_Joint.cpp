#include <unittest++/UnitTest++.h>
#include <mlog/Log.h>
#include <moodyn/components/Joint.h>
#include <moodyn/World.h>
#include <osg/io_utils>

using namespace moodyn;

TEST (HangingBody) {
	// Hang a body from a ball joint with a bit of offset
	osg::ref_ptr<Body> body = new Body;
	body->realize();
	osg::ref_ptr<Joint> joint = new Joint(Joint::BALL);
	joint->setAnchor(osg::Vec3(5,0,2));
	joint->attach(body.get());
	joint->realize();

	// Run the simulation for awhile
	const double dt = 0.01;
	for (double t = dt; t-dt/2.0 < 3.2; t += dt)
		World::instance().update(dt);
	
	// Check that it has moved but not fallen
	CHECK(body->getPosition().length() > 0.01);
	CHECK(body->getPosition().z() > -5.0);
	
	// Delete the joint and make sure it falls
	joint = NULL;
	for (double t = dt; t-dt/2.0 < 3.2; t += dt)
		World::instance().update(dt);
	CHECK(body->getPosition().z() < -10.0);
}

TEST (JointedBodies) {
	/// \todo Test jointing two bodies programatically, both as one being children of the other and as separate
}
