/// \todo Update ObjectIO tests with some other components than plugin dependent ones.
#ifndef MOON_NO_PHYSICS

#include <unittest++/UnitTest++.h>
#include <moodyn/objects/DynamicPhysicalObject.h>
#include <moon/ObjectFactory.h>
#include <moon/Modifier.h>
#include <mlog/Log.h>
#include <mdraw/utils.h>
#include <osg/io_utils>

using namespace mlog;
using namespace moon;
using namespace moodyn;

struct RatherComplexObjectFixture {
	RatherComplexObjectFixture()
	{
		object = new DynamicPhysicalObject;
		object->setName("object");
		object->setTag("testing");
		
		VisualModel *model = new VisualModel("test.ive", osg::Matrix::translate(osg::Vec3(5,3,7)) 
											 *osg::Matrix::rotate(M_PI, osg::Vec3(0,0,1)), false);
		object->addComponent(model);
		BaseObject *child = new BaseObject;
		child->setName("child");
		child->setPosition(1,2,3);
		child->setAttitude(0.1,0.5,0.3);
		object->addComponent(child);
		
		moodyn::Geometry *geo = new moodyn::Geometry;
		geo->addShape(moodyn::Geometry::BOX, 3, 2, 1);
		geo->addShape(moodyn::Geometry::SPHERE, 0.5, 0, 0, 0, osg::Matrix::translate(osg::Vec3(0,2,3)));
		geo->addShape(moodyn::Geometry::CAPSULE, 1, 2, 0, 0, osg::Matrix::rotate(osg::Vec3(1,0,0), osg::Vec3(0,1,0)));
		geo->addShape(moodyn::Geometry::CYLINDER, 3, 2);
		geo->addShape(moodyn::Geometry::PLANE, 0, 0, 1, 3);
		object->addComponent(geo);
		
		moodyn::Body *body = new moodyn::Body;
		body->setMass(3);
		object->addComponent(body);
		maudio::SingleSource *source = new maudio::SingleSource;
		source->setName("test_sound");
		source->setLooping(true);
		source->setPosition(osg::Vec3(0,1,3));
		object->addComponent(source);
		Table *table = new Table;
		table->add(1,2);
		table->add(2,5);
		source->addModifier(table);
		objects.push_back(object.get());
	}
	
	osg::ref_ptr<DynamicPhysicalObject> object;
	ObjectFactory::ObjectList objects;
};

TEST_FIXTURE(RatherComplexObjectFixture, RatherComplexObjectFixture)
{
	object->initialize();
	CHECK_EQUAL(1u, object->getNumChildren());
	CHECK(object->getGeometry() != NULL);
	CHECK(object->getBody() != NULL);
	CHECK(object->getTransform()->getNumChildren() >= 0);
}

TEST_FIXTURE(RatherComplexObjectFixture, ObjectIO)
{
	// Write the object to an XML element
	TiXmlElement *testElement = new TiXmlElement("test");
	ObjectFactory::instance().writeObjects(objects, testElement);
	if (getDebugLevel() >= 2) {
		std::cout << "\nRatherComplexObject object XML:\n";
		testElement->Print(stdout, 0);
		std::cout << "\n\n";
	}

	// Read it back
	int debugLevel = getDebugLevel(); setDebugLevel(-3); // avoid error printout
	ObjectFactory::ObjectList objs = ObjectFactory::instance().parseObjects(testElement);
	setDebugLevel(debugLevel);
	CHECK_EQUAL(1u, objs.size());
	DynamicPhysicalObject *obj = dynamic_cast<DynamicPhysicalObject*> (objs[0].get());
	obj->initialize();

	// Check that the read object is equal to the written object
	CHECK_EQUAL(1u, obj->getNumChildren());
	CHECK_EQUAL("object", obj->getName());
	CHECK_EQUAL("child", obj->getChild(0)->getName());
	CHECK(obj->hasTag("testing"));
	CHECK_ARRAY_CLOSE(osg::Vec3(1,2,3), obj->getChild(0)->getPosition(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(0.1f,0.5f,0.3f), obj->getChild(0)->getAttitude(), 3, 1e-5);
	CHECK(obj->getGeometry() != NULL);
	CHECK(obj->getBody() != NULL);
	CHECK_EQUAL(object->getGeometry()->getNumShapes(), obj->getGeometry()->getNumShapes());
	CHECK_EQUAL(object->getBody()->getMass(), obj->getBody()->getMass());
	// Check that transforms correspond
	CHECK_ARRAY_CLOSE(object->getChild(0)->getTransform()->getMatrix().getTrans(),
					  obj->getChild(0)->getTransform()->getMatrix().getTrans(), 
					  3, 1e-5);
	CHECK_ARRAY_CLOSE(object->getChild(0)->getTransform()->getMatrix().getRotate(),
					  obj->getChild(0)->getTransform()->getMatrix().getRotate(), 
					  4, 1e-5);
	delete testElement;
}

TEST_FIXTURE(RatherComplexObjectFixture, TemplateObjectIO)
{
	ObjectFactory::instance().addTemplate(object.get());
	osg::ref_ptr<DynamicPhysicalObject> instance = (DynamicPhysicalObject*) ObjectFactory::instance().createInstance(object.get());
	CHECK_EQUAL(object.get(), instance->getTemplate());
	instance->setPosition(5,10,15);
	
	// Write the object to an XML element
	TiXmlElement *testElement = new TiXmlElement("test");
	ObjectFactory::ObjectList instances;
	instances.push_back(instance.get());
	ObjectFactory::instance().writeObjects(instances, testElement);
	if (getDebugLevel() >= 2) {
		std::cout << "\nRatherComplexObject template/instance XML:\n";
		testElement->Print(stdout, 0);
		std::cout << "\n\n";
	}

	ObjectFactory::instance().removeTemplate(object.get());
	delete testElement;
	ObjectFactory::instance().clearTemplates();
}

#endif
