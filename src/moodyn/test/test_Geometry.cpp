#include <unittest++/UnitTest++.h>
#include <moodyn/components/Geometry.h>
#include <mdraw/utils.h>
#include <osgDB/ReadFile>

using namespace moodyn;

struct GeometryFixture {
	GeometryFixture() {
		geo = new Geometry;
		geo->addShape(Geometry::BOX, 1, 1, 1);
	}
	osg::ref_ptr<Geometry> geo;
};

TEST_FIXTURE (GeometryFixture, GeometryShapes) {
	CHECK_EQUAL(1u, geo->getNumShapes());
	geo->addShape(Geometry::SPHERE, 1, 0, 0, 0, osg::Matrix::translate(1,0,1));
	CHECK_EQUAL(2u, geo->getNumShapes());
	CHECK_ARRAY_CLOSE(osg::Vec3(0,0,0), geo->getShape(0).M.getTrans(), 3, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec3(1,0,1), geo->getShape(1).M.getTrans(), 3, 1e-5);
	// Add a cylinder
	geo->addShape(Geometry::CYLINDER, 1, 1, 0, 0, osg::Matrix::translate(0,0,-1));
	CHECK_EQUAL(3u, geo->getNumShapes());
	
	// Check debug node (crudely)
	osg::ref_ptr<osg::Node> node = geo->createDebugNode();
	CHECK(node.valid());
	if (node.valid()) {
		osg::BoundingBox bbox = mdraw::getBoundingBox(node.get());
		CHECK_CLOSE(-1.5, bbox.zMin(), 1e-5);
		CHECK_CLOSE(2.0, bbox.zMax(), 1e-5);
		CHECK_CLOSE(2.0, bbox.xMax(), 1e-5);
		CHECK_CLOSE(1.0, bbox.yMax(), 1e-5);
	}
}

TEST_FIXTURE (GeometryFixture, SimpleContact) {
	osg::ref_ptr<Geometry> geo2 = new Geometry;
	geo2->addShape(Geometry::SPHERE, 1);

	geo->realize();
	geo2->realize();
	
	// Check contact between two geometries
	CHECK(geo2->checkContact(geo.get()));
	
	// Move away geo2 and check no contact
	geo2->setTransformation(osg::Matrix::translate(3,0,0));
	CHECK_ARRAY_CLOSE(osg::Vec3(3,0,0), geo2->getPosition(), 3, 1e-5);
	CHECK(!geo2->checkContact(geo.get()));
	
	// Move back a bit and check contact
	geo->setTransformation(osg::Matrix::translate(2,0,0));
	CHECK(geo->checkContact(geo2.get()));
	
	// Remove geoms for geo2 and check no contact
	geo2->unrealize();
	CHECK(!geo->checkContact(geo2.get()));
}

TEST_FIXTURE (GeometryFixture, NodeToGeometry) {
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("dumptruck.osg");
	if (node.valid()) {
		// Create mesh geometry from node
		osg::ref_ptr<Geometry> geo2 = new Geometry;
		geo2->addMesh(node.get());
		CHECK_EQUAL(1u, geo2->getNumShapes());

		// Create primitive geometry from node
		osg::ref_ptr<Geometry> geo3 = new Geometry;
		geo3->addShapesFromBounds(node.get());
		CHECK(geo3->getNumShapes() > 0);
	}
}

