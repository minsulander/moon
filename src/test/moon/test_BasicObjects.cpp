#include <unittest++/UnitTest++.h>
#include <moon/objects/BaseObject.h>
#include <cmath>

using namespace moon;

class CopyTestObject : public BaseObject {
public:
	CopyTestObject(int val=0) : BaseObject(), value(val) {}
	CopyTestObject(const CopyTestObject& obj, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
	: BaseObject(obj), value(obj.value) {}
	
	META_Object(moon, CopyTestObject);
	void setValue(int val) { value = val; }
	int getValue() { return value; }
private:
	int value;
};

TEST (CopyTest) {
	osg::ref_ptr<CopyTestObject> test1 = new CopyTestObject(4711);
	test1->addChild(new CopyTestObject(5015));
	CHECK_EQUAL(1u, test1->getNumChildren());
	test1->setName("zetestobject");
		
	osg::ref_ptr<CopyTestObject> test2 = (CopyTestObject*)test1->clone(osg::CopyOp::SHALLOW_COPY);
	test2->initialize();
	CHECK_EQUAL(4711, test2->getValue());
	CHECK_EQUAL("zetestobject", test2->getName());
	CHECK(test1->getTransform() != test2->getTransform());
	CHECK_EQUAL(1u, test2->getNumChildren());
}

TEST (BasicMovement) {
	osg::ref_ptr<BaseObject> obj = new BaseObject;
	
	CHECK_ARRAY_EQUAL(osg::Vec3(0,0,0), obj->getPosition(), 3);
	CHECK_ARRAY_EQUAL(osg::Vec3(0,0,0), obj->getAttitude(), 3);
	
	// Basic movement
	obj->move(5);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,5,0), obj->getPosition(), 3, 1e-5);
	obj->move(10,5,10);
	CHECK_ARRAY_CLOSE(osg::Vec3(10,10,10), obj->getPosition(), 3, 1e-5);
	obj->move(10);
	CHECK_ARRAY_CLOSE(osg::Vec3(10,20,10), obj->getPosition(), 3, 1e-5);
	
	// Reset position
	obj->setPosition(osg::Vec3(0,0,0));
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,0), obj->getPosition(), 3, 1e-5);
	
	// 90 degree attitude changes and movements
	obj->setAttitude(0, M_PIf/2, 0);
	obj->move(10);
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,10), obj->getPosition(), 3, 1e-5);
	obj->setAttitude(M_PIf/2, 0, 0);
	obj->move(10);
	CHECK_ARRAY_CLOSE(osg::Vec3(10,0,10), obj->getPosition(), 3, 1e-5);
	obj->setAttitude(0, 0, 0);
	obj->move(10);
	CHECK_ARRAY_CLOSE(osg::Vec3(10,10,10), obj->getPosition(), 3, 1e-5);
	
	// 45 degree yaw and movement
	obj->yaw(M_PIf/4);
	obj->move(10*sqrtf(2));
	CHECK_ARRAY_CLOSE(osg::Vec3(20,20,10), obj->getPosition(), 3, 1e-5);
	// 45 degree pitch and movement
	obj->pitch(M_PIf/4);
	obj->move(10*sqrtf(2));
	CHECK_CLOSE(20, obj->getPosition().z(), 1e-5);
	
	// 90 degree roll right
	obj->roll(M_PIf/2);
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PIf/4, M_PIf/4, M_PIf/2), obj->getAttitude(), 3, 1e-5);
	// yawing 45 degree right should now result in zero pitch
	obj->yaw(M_PIf/4);
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PIf/4, 0, M_PIf/2), obj->getAttitude(), 3, 1e-5);
}

TEST (ChildObject) {
	osg::ref_ptr<BaseObject> parent = new BaseObject, child = new BaseObject;
	parent->addChild(child.get());
	
	CHECK_EQUAL(parent.get(), child->getParent());
	CHECK_EQUAL(1u, parent->getNumChildren());
	CHECK_EQUAL(child.get(), parent->getChild(0));
	
	child->setPosition(0, 0, 10);
	parent->setPosition(10, 10, 0);
	// Child position is relative to parent
	CHECK_ARRAY_CLOSE(osg::Vec3(0, 0, 10), child->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(10, 10, 10), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);
	// Parent attitude affects child world position
	parent->roll(M_PIf/2);
	CHECK_ARRAY_CLOSE(osg::Vec3(20,10,0), child->getWorldTransformMatrix().getTrans(), 3, 1e-5);
	
	// Add duplicate child
	parent->addChild(child.get());
	CHECK_EQUAL(1u, parent->getNumChildren());
	
	// Remove child
	parent->removeChild(child.get());
	CHECK_EQUAL(0u, parent->getNumChildren());
	CHECK(!child->getParent());
}

TEST (TwoObjectsMovement) {
	osg::ref_ptr<BaseObject> first = new BaseObject, second = new BaseObject;
	
	// Point at object, get relative azimuths and elevations between them
	second->setPosition(10, 0, 0);
	CHECK_CLOSE(M_PIf/2, first->getAzimuth(second.get()), 1e-5);
	first->pointAt(second.get());
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PIf/2, 0, 0), first->getAttitude(), 3, 1e-5);

	second->setPosition(0.01, -10, 0);
	CHECK_CLOSE(M_PIf/2, first->getAzimuth(second.get()), 0.01);
	first->pointAt(second.get());
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PIf, 0, 0), first->getAttitude(), 3, 0.01);
	
	first->setAttitude(0, 0, 0);
	second->setPosition(-10, 0, 0);
	CHECK_CLOSE(-M_PIf/2, first->getAzimuth(second.get()), 1e-5);
	first->pointAt(second.get());
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PIf*3.f/2, 0, 0), first->getAttitude(), 3, 1e-5);
	
	first->setAttitude(0, 0, 0);
	second->setPosition(-5, -5, 5*std::sqrt(2.0f));
	CHECK_CLOSE(-3.0*M_PIf/4, first->getAzimuth(second.get()), 1e-5);
	CHECK_CLOSE(M_PIf/4, first->getElevation(second.get()), 1e-5);
	first->pointAt(second.get());
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PIf*5.f/4, M_PIf/4, 0), first->getAttitude(), 3, 1e-5);
	
	// Check absolute azimuths/elevations
	first->setAttitude(M_PIf/4, M_PIf/4, 0);
	second->setPosition(10, 10, 0);
	CHECK_CLOSE(M_PIf/4, first->getAzimuth(second.get(), false), 1e-5);
	CHECK_CLOSE(0, first->getElevation(second.get(), false), 1e-5);
	CHECK_CLOSE(0, first->getAzimuth(second.get(), true), 1e-5);
	CHECK_CLOSE(-M_PIf/4, first->getElevation(second.get(), true), 1e-5);

	first->setAttitude(0, 0, M_PIf/2);
	first->pointAt(second.get());
	CHECK_ARRAY_CLOSE(osg::Vec3(M_PIf/4, 0, M_PIf/2), first->getAttitude(), 3, 1e-5);
}

TEST (FindRelated) {
	osg::ref_ptr<BaseObject> o1 = new BaseObject, o11 = new BaseObject, o111 = new BaseObject, o12 = new BaseObject;
	o1->setName("o1"); o11->setName("o11"); o111->setName("o111"); o12->setName("o12");
	o1->addChild(o11.get());
	o11->addChild(o111.get());
	o1->addChild(o12.get());
	CHECK_EQUAL(o12.get(), o11->findRelated("o12"));
	CHECK_EQUAL(o111.get(), o12->findRelated("o111"));
	CHECK_EQUAL(o11.get(), o1->findRelated("o11"));
	CHECK_EQUAL(o1.get(), o111->findRelated("o1"));
	
	osg::ref_ptr<BaseObject> o1c = new BaseObject(*o1.get());
	o1c->initialize();
	CHECK_EQUAL(o1->getNumChildren(), o1c->getNumChildren());
	CHECK_EQUAL(o1c->getChild(1), o1c->getChild(0)->findRelated("o12"));
	CHECK_EQUAL(o1c->getChild(0)->getChild(0), o1c->getChild(1)->findRelated("o111"));
}

