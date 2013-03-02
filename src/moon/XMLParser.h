#ifndef MOON_XMLPARSER_H
#define MOON_XMLPARSER_H

#include "Export.h"
#include <tinyxml.h>
#include <osg/Vec3>
#include <osg/Vec4>
#include <string>
#include <vector>

namespace moon
{
	
	/// \addtogroup core
	/// @{
	
	/// XML parser for configuriation and data specification XML files
	class MOON_EXPORT XMLParser
	{
	public:
		XMLParser();
		virtual ~XMLParser();
		
		static void initUnits(const std::string& unitsfilepath);
		
		static bool parseStringAttribute(std::string& str, const TiXmlElement *element, const std::string& name);
		static std::string parseStringAttribute(const TiXmlElement* element, const std::string& name, bool usedef = false, const std::string& def = "");
		static bool parseString(std::string& str, const TiXmlElement *element, const std::string& name, const std::string& attr = "value");
		static std::string parseString(const TiXmlElement* parent, const std::string& name, bool usedef = false, const std::string& def = "", const std::string& attr = "value");
		
		template<typename T> static bool parseValueAttribute(T& value, const TiXmlElement* xe, const std::string& attr)
		{
			int ret = xe->QueryValueAttribute(attr,&value);
			if (ret == TIXML_SUCCESS)
				return true;
			return false;		
		}

		static bool parseIntAttribute(int& i, const TiXmlElement* xe, const std::string& attr);
		static int parseIntAttribute(const TiXmlElement* xe, const std::string& attr, bool usedef = false, const int def = 0);
		static bool parseInt(int& i, const TiXmlElement* xe, const std::string& name, const std::string& unit = "", const std::string& attr = "value");
		static int parseInt(const TiXmlElement* parent, const std::string& name, const std::string& unit = "", bool usedef = false, const int def = 0, const std::string& attr = "value");

		static bool parseDoubleAttribute(double& i, const TiXmlElement* xe, const std::string& attr);
		static double parseDoubleAttribute(const TiXmlElement* xe, const std::string& attr, bool usedef = false, const double def = 0.0);
		static bool parseDouble(double& i, const TiXmlElement* xe, const std::string& name, const std::string& unit = "", const std::string& attr = "value");
		static double parseDouble(const TiXmlElement* parent, const std::string& name, const std::string& unit = "", bool usedef = false, const double def = 0.0, const std::string& attr = "value");

		static osg::Vec3 parseVector3String(const std::string& str);
		static bool parseVector3Attribute(osg::Vec3& v, const TiXmlElement* xe, const std::string& attr);
		static osg::Vec3 parseVector3Attribute(const TiXmlElement* xe, const std::string& attr, bool usedef = false, const osg::Vec3& def = osg::Vec3(0,0,0));
		static bool parseVector3(osg::Vec3& v, const TiXmlElement* xe, const std::string& name, const std::string& unit = "", const std::string& attr = "value");
		static osg::Vec3 parseVector3(const TiXmlElement* parent, const std::string& name, const std::string& unit = "", bool usedef = false, const osg::Vec3& def = osg::Vec3(0,0,0), const std::string& attr = "value");

		static osg::Vec4 parseVector4String(const std::string& str);
		static bool parseVector4Attribute(osg::Vec4& v, const TiXmlElement* xe, const std::string& attr);
		static osg::Vec4 parseVector4Attribute(const TiXmlElement* xe, const std::string& attr, bool usedef = false, const osg::Vec4& def = osg::Vec4(0,0,0,0));
		static bool parseVector4(osg::Vec4& v, const TiXmlElement* xe, const std::string& name, const std::string& unit = "", const std::string& attr = "value");
		static osg::Vec4 parseVector4(const TiXmlElement* parent, const std::string& name, const std::string& unit = "", bool usedef = false, const osg::Vec4& def = osg::Vec4(0,0,0,0), const std::string& attr = "value");

		static bool parseBooleanString(const std::string& str);
		static bool parseBooleanAttribute(bool& b, const TiXmlElement* xe, const std::string& attr);
		static bool parseBooleanAttribute(const TiXmlElement* element, const std::string& attr = "value", const bool usedef = false, const bool def = false);
		static bool parseBoolean(bool& b, const TiXmlElement* parent, const std::string& name, const std::string& attr = "value");
		static bool parseBoolean(const TiXmlElement* parent, const std::string& name, const bool usedef = false, const bool def = false, const std::string& attr = "value");

		static bool parseVector(std::vector<double>& V, const TiXmlElement* parent, const std::string& name, const bool fixed = false, const std::string& unit = "");
		static void parseTable(const TiXmlElement* parent, const std::string& name, std::vector<double>& x, std::vector<double>& y, const std::string& unit = "", const std::string& unit2 = "");
		static std::vector<std::string> parseStringListAttribute(const TiXmlElement* element, const std::string& name);
		
		static void setString(TiXmlElement* parent, const std::string& element, const std::string& value, const std::string& attr = "value");
		static void setInt(TiXmlElement* parent, const std::string& element, const int value, const std::string& attr = "value");
		static void setDouble(TiXmlElement* parent, const std::string& element, const double value, const std::string& attr = "value");
		static void setBoolean(TiXmlElement* parent, const std::string& element, const bool value, const std::string& attr = "value");
		static void setVector3(TiXmlElement* parent, const std::string& element, const osg::Vec3& value, const std::string& attr = "value");
		static void setVector4(TiXmlElement* parent, const std::string& element, const osg::Vec4& value, const std::string& attr = "value");
		
		static std::string currentFile;
	};
	
	class ParseException : public std::exception {
	public:
		ParseException(const std::string& nmessage = "", const TiXmlNode *nnode = NULL)
		{ 
			std::stringstream ss;
			node = nnode;
			ss << XMLParser::currentFile;
			if (node) {
				if (node->ToDocument()) 
					ss << ":" << node->ToDocument()->ErrorRow();
				else if (node->Row())
					ss << ":" << node->Row();
			}
			ss << ": ";
			ss << nmessage;
			message = ss.str();
		}
		~ParseException() throw() {}
		virtual const char* what() const throw()
		{
			return message.c_str();
		}
		std::string message;
		const TiXmlNode *node;
	};
	
	class ParseNoElementException : public ParseException {
	public:
		ParseNoElementException(const std::string& message = "", const TiXmlNode *node = NULL)
		: ParseException(message, node)
		{ }
	};
	
	/// @}
}

#endif
