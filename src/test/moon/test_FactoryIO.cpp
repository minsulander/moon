#include <unittest++/UnitTest++.h>
#include <moon/ObjectFactory.h>
#include <moon/XMLParser.h>
#include <iostream>

#ifdef WIN32
#	define TESTFILE "c:\\moon-factory-test.xml"
#   pragma warning(disable:4996) // warning about unlink() being deprecated
#else
#	include <unistd.h>
#	define TESTFILE "/tmp/moon-factory-test.xml"
#endif

using namespace moon;

ObjectFactory& factory = ObjectFactory::instance();

// Define some test objects to play with
namespace moontest {
	
	class ObjectA : public FactoryProduct {
	public:
		ObjectA() {}
		ObjectA(const ObjectA& object, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
		META_Object(test, ObjectA);
		virtual void parseXML(const TiXmlElement *element) {}
		virtual void writeXML(TiXmlElement *element) const {}
	};
	REGISTER_Object_Alias(test, ObjectA, AObject);
}
using namespace moontest;

namespace moon {
	
	class ObjectB : public FactoryProduct {
	public:
		META_Object(moon, ObjectB);

		ObjectB() 
			: param(0) {}
		ObjectB(const ObjectB& object, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) 
			: param(object.param) {}
		
		virtual void parseXML(const TiXmlElement *element)
		{
			param = XMLParser::parseInt(element, "parameter", "", true, param);
		}
		
		virtual void writeXML(TiXmlElement *element) const
		{
			// Here's an example of how to make instances only write out differences from their templates...
			const ObjectB *temp = (const ObjectB*) getTemplate();
			if (!temp || param != temp->param)
				XMLParser::setInt(element, "parameter", param);
		}
		
		int param;
	};
	REGISTER_Object(moon, ObjectB);
}

#define TEST_DOCUMENT "\
<moon>\
<test_ObjectA name='a1' />\
<AObject name='a2' />\
<test_ObjectA/>\
<moon_ObjectB name='b1'>\
<parameter value='4711'/>\
</moon_ObjectB>\
<ObjectB>\
<parameter value='555'/>\
</ObjectB>\
</moon>\
"

TEST(SimpleIO) {
	// Test reading objects from an XML document	
	{
		ObjectFactory::ObjectList objects = factory.parseObjects(TEST_DOCUMENT);
		CHECK_EQUAL(5u, objects.size());
		CHECK(objects[2]->getName().length() > 0);
		CHECK_EQUAL("ObjectA", objects[1]->className());
		CHECK_EQUAL("ObjectB", objects[4]->className());
		ObjectB *b = dynamic_cast<ObjectB*> (objects[3].get());
		CHECK(b);
		CHECK_EQUAL(4711, b->param);
	}

	// Test for document errors
	{
		// Non-existent document
		CHECK_THROW(factory.loadObjects("non-existent-file.xml"), FactoryIOException);
		// Non-existent object specified
		CHECK_THROW(factory.parseObjects("<moon><NonExistentObject/></moon>"), NoSuchObjectException);
		// Wrong root node
		CHECK_THROW(factory.parseObjects("<blah><moreBS></blah>"), ParseNoElementException);
	}
	
	// Test writing objects to an XML document
	{
		ObjectFactory::ObjectList objects;
		ObjectA *a = new ObjectA;
		ObjectB *b = new ObjectB;
		b->param = 5550;
		objects.push_back(a);
		objects.push_back(b);
		
		factory.saveObjects(objects, TESTFILE);
	}

	// Test reading objects back
	{
	  factory.clearTemplates();
		ObjectFactory::ObjectList objects = factory.loadObjects(TESTFILE);
		ObjectA *a = dynamic_cast<ObjectA*> (objects[0].get());
		ObjectB *b = dynamic_cast<ObjectB*> (objects[1].get());
		CHECK(a && b);
		CHECK_EQUAL(5550, b->param);
	}
	unlink(TESTFILE);
}

#define TEMPLATE_DOCUMENT "\
<moon>\
	<templates>\
		<test_ObjectA name='A1'/>\
		<ObjectB name='B1'><parameter value='4711'/></ObjectB>\
		<ObjectB name='B2'><parameter value='4712'/></ObjectB>\
	</templates>\
	<A1 name='a1'/>\
	<B1 name='b1'/>\
	<B2 name='b2'/>\
	<ObjectB name='b3'><parameter value='4713'/></objectB>\
</moon>\
"

TEST(TemplateIO) {
	// Load objects from the above "document"
	{
		ObjectFactory::ObjectList objects = factory.parseObjects(TEMPLATE_DOCUMENT, true, true);
		CHECK_EQUAL(4u, objects.size());
		ObjectB *b1 = dynamic_cast<ObjectB*> (objects[1].get());
		ObjectB *b2 = dynamic_cast<ObjectB*> (objects[2].get());
		ObjectB *b3 = dynamic_cast<ObjectB*> (objects[3].get());
		CHECK_EQUAL(4711, b1->param);
		CHECK_EQUAL(4712, b2->param);
		CHECK_EQUAL(4713, b3->param);
		CHECK(b2->getTemplate());
		CHECK(!b3->getTemplate());
		
		factory.saveObjects(objects, TESTFILE);
	}
	
	// Try reading them back again and make sure it hasn't changed
	{
		factory.clearTemplates();
		CHECK_EQUAL(0u, factory.getNumTemplates());
		ObjectFactory::ObjectList objects = factory.loadObjects(TESTFILE);
		CHECK_EQUAL(4u, objects.size());
		ObjectB *b2 = dynamic_cast<ObjectB*> (objects[2].get());
		ObjectB *b3 = dynamic_cast<ObjectB*> (objects[3].get());
		CHECK_EQUAL(4712, b2->param);
		CHECK_EQUAL(4713, b3->param);
		CHECK(b2->getTemplate());
		CHECK(!b3->getTemplate());
	}
	unlink(TESTFILE);
}
