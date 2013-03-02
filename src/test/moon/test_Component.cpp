#include <unittest++/UnitTest++.h>
#include <moon/components/Component.h>

using namespace moon;

TEST (ComponentBasics) {
	osg::ref_ptr<ComponentContainer> container = new ComponentContainer;
	osg::ref_ptr<Component> comp1 = new Component;
	osg::ref_ptr<Component> comp2 = new Component;
	// Adding a component should be reflected by its owner and size of container
	CHECK_EQUAL(0u, container->getNumComponents());
	CHECK(comp1->getContainer() == NULL);
	container->addComponent(comp1.get());
	container->addComponent(comp2.get());
	CHECK_EQUAL(2u, container->getNumComponents());
	CHECK_EQUAL(container.get(), comp1->getContainer());
	CHECK_EQUAL(container.get(), comp2->getContainer());
	// Setting a tag should work
	comp1->setTag("test");
	CHECK(comp1->hasTag("test"));
	CHECK(!comp1->hasTag("other"));
	// Getting by tag should work
	CHECK(container->getComponentByTag("test") == comp1.get());
	CHECK(container->getComponentByTag("other") == NULL);
	comp2->setTag("test");
	comp2->setTag("other");
	CHECK(comp2->hasTag("test"));
	// getComponentByTag() only returns first component with specified tag
	CHECK(container->getComponentByTag("test") == comp1.get());
	CHECK(container->getComponentByTag("other") == comp2.get());
	// Check recursive realize
	CHECK(!comp1->isRealized());
	CHECK(!comp2->isRealized());
	container->realize();
	CHECK(comp1->isRealized());
	CHECK(comp2->isRealized());
	// Check container destructor
	container = NULL;
	CHECK(comp1->getContainer() == NULL);
	CHECK(comp2->getContainer() == NULL);
}


