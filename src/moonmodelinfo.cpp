#include <mlog/Log.h>
#include <osg/ArgumentParser>
#include <osgDB/ReadFile>
#include <mdraw/utils.h>
//#include <moodyn/Geometry.h>
#include <moon/components/VisualModel.h>
#include <osg/io_utils>

using namespace moon;
using namespace mlog;

osg::ArgumentParser *arguments = NULL;

void showInfo(const std::string& filename)
{
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(filename);
	if (!node)
		return;
	dout(0) << "--- " << filename << " ---\n";
	
	if (arguments->read("-bound")) {
		osg::BoundingSphere bound = node->getBound();
		dout(0) << "Bounding Sphere:\n";
		dout(0) << "  center " << bound.center() << "\n";
		dout(0) << "  radius " << bound.radius() << "\n";
	}
	
	if (arguments->read("-bbox")) {
		osg::BoundingBox bbox = mdraw::getBoundingBox(node.get());
		dout(0) << "Bounding Box:\n";
		dout(0) << "  center " << bbox.center() << "\n";
		dout(0) << "  size " << osg::Vec3(bbox.xMax()-bbox.xMin(), bbox.yMax()-bbox.yMin(), bbox.zMax()-bbox.zMin()) << "\n";
		dout(0) << "  min " << osg::Vec3(bbox.xMin(), bbox.yMin(), bbox.zMin()) << "\n";
		dout(0) << "  max " << osg::Vec3(bbox.xMax(), bbox.yMax(), bbox.zMax()) << "\n";
	}
	
        int verbosity = 0;
        if (arguments->read("-nodes", verbosity) || arguments->read("-nodes")) {
                dout(0) << "Nodes (verbosity " << verbosity << "):\n";
                dout(0) << mdraw::getNodeString(node.get(), verbosity) << "\n";
	}
	
	if (arguments->read("-special")) {
		dout(0) << "Special Nodes:\n";
		osg::ref_ptr<osg::Node> specnode = VisualModel::extractSpecialNodes(node.get());
		if (!specnode)
			dout(0) << "  no special nodes\n";
		else
			dout(0) << mdraw::getNodeString(specnode.get()) << "\n";
	}
	/*
	if (arguments->read("-geo")) {
		dout(0) << "Geometry XML:\n";
		osg::ref_ptr<moodyn::Geometry> geo = new moodyn::Geometry;
		geo->addShapesFromBounds(node.get());
		TiXmlElement *element = new TiXmlElement("Geometry");
		geo->writeXML(element);
		element->Print(stdout, 0);
		delete element;
		dout(0) << "\n";
	}
	 */
}

void usage()
{
	dout(0) << "usage: moonmodelinfo <arguments> <model file(s)>\n"
			<< "  -bound     bounding sphere\n"
			<< "  -bbox      bounding box\n"
			<< "  -nodes     node hierarchy\n"
			<< "  -special   parse special tagged nodes\n"
			<< "  -geo       geometry from bounds\n";
}

int main(int argc, char *argv[])
{
	arguments = new osg::ArgumentParser(&argc, argv);
	if (arguments->read("-h") || arguments->read("-help") || arguments->read("--help") || argc == 1) {
		usage();
		exit(0);
	}
	for (int i = 1; i < arguments->argc(); i++) {
		if (!arguments->isOption(i))
			showInfo((*arguments)[i]);
	}		
	
}
