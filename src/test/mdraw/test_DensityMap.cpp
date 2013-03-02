#include <unittest++/UnitTest++.h>
#include <mdraw/DensityMap.h>
#include <osg/io_utils>
#include <iostream>

using namespace mdraw;

unsigned int TEST_IMAGE[] = { 0xFFFFFFFF, 0x00000000, 0x00008080, 0x000F0F40 };

struct TestMapFixture {
	
	
	TestMapFixture()
	{
		testImage = new osg::Image;
		testImage->setImage(2, 2, 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) TEST_IMAGE, osg::Image::NO_DELETE);
		testMap = new DensityMap(testImage.get());
		testMap->setBounds(0,1000,0,1000);
		testMap->setDensity(40);
	}

	osg::ref_ptr<osg::Image> testImage;
	osg::ref_ptr<DensityMap> testMap;
};

// The test image above should correspond to the correct colors
TEST_FIXTURE (TestMapFixture, TestImageSetup) {
	CHECK_ARRAY_CLOSE(osg::Vec4(1,1,1,1), testImage->getColor(0,0), 4, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec4(0,0,0,0), testImage->getColor(1,0), 4, 1e-5);
	CHECK_ARRAY_CLOSE(osg::Vec4(0.5f,0.5f,0,0), testImage->getColor(0,1), 4, 0.01);
	CHECK_ARRAY_CLOSE(osg::Vec4(0.25f,0.06f,0.06f,0), testImage->getColor(1,1), 4, 0.01);
}

TEST_FIXTURE (TestMapFixture, PixelDensities) {
	CHECK_CLOSE(10, testMap->getPixelDensity(0,0), 1e-5);
	CHECK_CLOSE(10, testMap->getPixelDensity(0,0, DensityMap::CH_A), 0.05);
	CHECK_CLOSE(0, testMap->getPixelDensity(1,0), 1e-5);
	CHECK_CLOSE(5, testMap->getPixelDensity(0,1), 0.05);
	CHECK_CLOSE(5, testMap->getPixelDensity(0,1, DensityMap::CH_G), 0.05);
	CHECK_CLOSE(0, testMap->getPixelDensity(0,1, DensityMap::CH_B), 0.05);
	CHECK_CLOSE(2.5, testMap->getPixelDensity(1,1, DensityMap::CH_R), 0.01);
	CHECK_CLOSE(0.6, testMap->getPixelDensity(1,1, DensityMap::CH_G), 0.05);
	CHECK_CLOSE(0.6, testMap->getPixelDensity(1,1, DensityMap::CH_B), 0.05);
	CHECK_CLOSE(0, testMap->getPixelDensity(1,1, DensityMap::CH_A), 0.05);
}

TEST_FIXTURE (TestMapFixture, Positions) {
	testMap->generate();
	CHECK_CLOSE(17u, testMap->getNumPositions(), 1u);
	for (unsigned int i = 0; i < testMap->getNumPositions(); i++) {
		osg::Vec3 p = testMap->getPosition(i);
		CHECK(p.x() >= testMap->getBounds().xMin());
		CHECK(p.x() <= testMap->getBounds().xMax());
		CHECK(p.y() >= testMap->getBounds().yMin());
		CHECK(p.y() <= testMap->getBounds().yMax());
	}
}
