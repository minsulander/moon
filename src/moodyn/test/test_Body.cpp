#include <unittest++/UnitTest++.h>
#include <mlog/Log.h>
#include <moodyn/components/Body.h>
#include <moodyn/World.h>

using namespace moodyn;

TEST (BodyParameters) {
	osg::ref_ptr<Body> body = new Body;
	body->realize();
	
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,0), body->getPosition(), 3, 1e-5);
	body->setPosition(osg::Vec3(0,0,10));
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,10), body->getPosition(), 3, 1e-5);
	CHECK(body->getRotation().zeroRotation());
	body->setVelocity(osg::Vec3(1,2,3));
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,3), body->getVelocity(), 3, 1e-5);
	body->setAngularVelocity(osg::Vec3(1,2,3));
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,3), body->getAngularVelocity(), 3, 1e-5);
	
	body->setMass(47.11);
	CHECK_CLOSE(47.11, body->getMass(), 1e-5);
}

TEST (Gravity) {
	osg::ref_ptr<Body> body = new Body;
	body->realize();
	
	body->setPosition(osg::Vec3(0,0,9.81f));
	body->setMass(1);
	CHECK_CLOSE(1, body->getMass(), 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,9.81f), body->getPosition(), 3, 1e-5);
	
	const double dt = 0.001;
	for (double t = dt; t-dt/2.0 < 1.0; t += dt) {
		World::instance().update(dt);
	}
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,9.81f/2.0f), body->getPosition(), 3, 0.01);
}
