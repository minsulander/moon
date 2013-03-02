#include <unittest++/UnitTest++.h>
#include <moon/XMLParser.h>
#include <iostream>
#include <sstream>

using namespace moon;

#define TEST_DOCUMENT "\
<test>\
	<weight unit='kg' value='100' value2='200'/>\
	<weight2 unit='stone'> 31.5 </weight2>\
	<theTable unit='ft' unit2='ft lbf'>\
		1	10\
		2	20\
		3	30\
	</theTable>\
	<theVector value='1,2,3' unit='meter'/>\
	<theMatrix unit='metres'>\
		1 2 3\
		4 5 6\
		7 8 9\
	</theMatrix>\
	<theBigMatrix unit='meter'>\
		1 2 3 4 5\
		6 7 8 9 10\
		11 12 13 14 15\
	</theBigMatrix>\
	<theBigVector unit='meter'>\
		1 2 3 4 5 6 7 8 9 10 11 12 13\
	</theBigVector>\
	\
	<theBrokenElement values='100'/>\
	<theBrokenElement2 value='twohundred'/>\
	<theElementWithoutUnit value='100' unit='m^2'/>\
	<theBrokenTable>\
		1	10\
		2	20	20\
	</theBrokenTable>\
	<theBrokenVector value='1,2'/>\
	<theBrokenMatrix>\
		1 2 3\
		4 5 6\
		7\
	</theBrokenMatrix>\
	<theBrokenBigMatrix>\
		1 2 3 4 5\
		6 7 8 9 10\
		11 12 13 14 15 16\
	</theBrokenBigMatrix>\
	<theBrokenBigVector>\
		1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\
	</theBrokenBigVector>\
</test>\
"

TEST(XMLParser) {
	//XMLParser::instance().getPath().add("../data");
	TiXmlDocument doc;
	doc.Parse(TEST_DOCUMENT);
	TiXmlHandle hdoc(&doc);
	TiXmlElement *root = hdoc.FirstChildElement().Element();
	CHECK_EQUAL("test", root->Value());
	
	std::string str;
	CHECK(XMLParser::parseString(str, root, "weight"));
	CHECK(!XMLParser::parseString(str, root, "weight", "blah"));
	TiXmlElement *weightElement = root->FirstChildElement("weight");
	CHECK(weightElement);
	CHECK(XMLParser::parseStringAttribute(str, weightElement, "value"));
	CHECK(!XMLParser::parseStringAttribute(str, weightElement, "blah"));		  
	
	double val = 0;
	// unit conversion
	val = XMLParser::parseDouble(root, "weight", "lb");
	CHECK_CLOSE(220.46, val, 0.01);
	// another attribute - so that an element may have several values with the same unit
	val = XMLParser::parseDouble(root, "weight", "stone", false, 0, "value2");
	CHECK_CLOSE(31.5, val, 0.1);
	// using text instead of 'value' attribute
	val = XMLParser::parseDouble(root, "weight2", "kg");
	CHECK_CLOSE(200, val, 0.1);
	// non-existing element
	val = XMLParser::parseDouble(root, "another", "", true, 500);
	CHECK_CLOSE(500, val, 0.1);
	// table
	std::vector<double> x,y;
	XMLParser::parseTable(root, "theTable", x, y, "m", "N m");
	CHECK_EQUAL(3u, x.size());
	CHECK_EQUAL(3u, y.size());
	CHECK_CLOSE(0.3048, x[0], 0.01);
	CHECK_CLOSE(13.56, y[0], 0.01);
	// vector
	osg::Vec3 v = XMLParser::parseVector3(root, "theVector", "feet");
	CHECK_CLOSE(3.28, v.x(), 0.01);
	CHECK_CLOSE(6.56, v[1], 0.01);
	CHECK_CLOSE(9.84, v[2], 0.01);
	// default vector value
	v = XMLParser::parseVector3(root, "anotherVector", "", true, osg::Vec3(1,2,3) );
	CHECK_CLOSE(1, v[0], 0.01);
	CHECK_CLOSE(2, v[1], 0.01);
	CHECK_CLOSE(3, v[2], 0.01);
	
	// large vector, fixed size
	std::vector<double> V;
	V.resize(13);
	CHECK(XMLParser::parseVector(V, root, "theBigVector", true, "feet"));
	CHECK_THROW(XMLParser::parseVector(V, root, "theBrokenBigVector", true, "feet"), ParseException);
	
	// large vector, dynamic size
	V.clear();
	CHECK(XMLParser::parseVector(V, root, "theBigVector", false, "feet"));
	CHECK_EQUAL(13u, V.size());
	XMLParser::parseVector(V, root, "theBrokenBigVector", false, "feet");
	CHECK_EQUAL(15u, V.size());
	
	/*
	// matrix
	Eigen::Matrix3d M = XMLParser::parseMatrix3(root, "theMatrix", "feet");
	CHECK_CLOSE(16.40, M(1,1), 0.01);
	// default matrix value
	M = XMLParser::parseMatrix3(root, "anotherMatrix", "", true, Eigen::Matrix3d::identity());
	CHECK_EQUAL(1, M.determinant());
	// large dynamic matrix
	Eigen::MatrixXd X(3,5);
	XMLParser::parseMatrix(root, "theBigMatrix", X, "feet");
	CHECK_CLOSE(45.9, X(2,3), 0.1);
	// large dynamic vector
	Eigen::VectorXd V(13);
	XMLParser::parseVector(root, "theBigVector", V, "feet");
	CHECK_CLOSE(26.25, V[7], 0.1);
	*/
	// ERRORS
	CHECK_THROW(XMLParser::parseBoolean(root, "nonexistent"), ParseNoElementException);
	CHECK_THROW(XMLParser::parseInt(root, "theBrokenElement"), ParseException);
	CHECK_THROW(XMLParser::parseInt(root, "theBrokenElement2"), ParseException);
	CHECK_THROW(XMLParser::parseInt(root, "theElementWithoutUnit"), ParseException);
	CHECK_THROW(XMLParser::parseTable(root, "theBrokenTable", x, y), ParseException);
	CHECK_THROW(XMLParser::parseVector3(root, "theBrokenVector"), ParseException);
	/*
	CHECK_THROW(XMLParser::parseMatrix3(root, "theBrokenMatrix"), ParseException);
	CHECK_THROW(XMLParser::parseMatrix(root, "theBrokenBigMatrix", X), ParseException);
	CHECK_THROW(XMLParser::parseVector(root, "theBrokenBigVector", V), ParseException);
	 */
}
