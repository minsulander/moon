#include "XMLParser.h"
#include "units/units.h"

#include <sstream>

#ifdef _MSC_VER
// Disable warning about conversion from double to float
#pragma warning(disable:4244)
#endif

namespace moon
{
	
	XMLParser::XMLParser()
	{
	}
	
	XMLParser::~XMLParser()
	{
	}
	
	void XMLParser::initUnits(const std::string& unitsfilepath)
	{
		units::initialize(unitsfilepath);
	}
	
	bool XMLParser::parseStringAttribute(std::string& str, const TiXmlElement* xe, const std::string& name)
	{
		if (xe->Attribute(name)) {
			str = *xe->Attribute(name);
			return true;
		}
		return false;
	}
	
	std::string XMLParser::parseStringAttribute(const TiXmlElement* xe, const std::string& name, bool usedef, const std::string& def)
	{
		if (xe->Attribute(name))
			return *xe->Attribute(name);
		else if (usedef)
			return def;
		else
			throw ParseNoElementException("Attribute '" + name + "' missing in element '" + xe->Value() + "'");
	}
	
	bool XMLParser::parseString(std::string& str, const TiXmlElement *parent, const std::string& name, const std::string& attr)
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (xe) {
			if (attr == "text") {
				str = xe->GetText();
				return true;
			} else if (xe->Attribute(attr)) {
				str = *xe->Attribute(attr);
				return true;
			}
		}
		return false;
	}
	
	std::string XMLParser::parseString(const TiXmlElement* parent, const std::string& name, bool usedef, const std::string& def, const std::string& attr)
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'");
		}
		if (attr == "text")
			return xe->GetText();
		else if (xe->Attribute(attr))
			return *xe->Attribute(attr);
		else if (usedef)
			return def;
		else
			throw ParseNoElementException("Element '" + name + "' does not have attribute '" + attr + "'");
	}
	
	bool XMLParser::parseIntAttribute(int& val, const TiXmlElement* xe, const std::string& attr)
	{
		int ret = xe->QueryIntAttribute(attr,&val);
		if (ret == TIXML_SUCCESS)
			return true;
		return false;
	}
	
	int XMLParser::parseIntAttribute(const TiXmlElement* xe, const std::string& attr, bool usedef, const int def)
	{
		int val;
		int ret = xe->QueryIntAttribute(attr,&val);
		if (ret == TIXML_WRONG_TYPE)
			throw ParseException("wrong type of value for attribute '" + attr + "' in '" + xe->Value() + "'", xe);
		else if (ret != TIXML_SUCCESS) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("no value for attribute '" + attr + "' in '" + xe->Value() + "'");
		}
		return val;		
	}
	
	bool XMLParser::parseInt(int& val, const TiXmlElement* parent, const std::string& name, const std::string& unit, const std::string& attr)
	{
		std::string str;
		if (!parseString(str, parent, name, attr))
			return false;
		val = atoi(str.c_str());
		// Unit conversion
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (xe->Attribute("unit")) {
			if (unit == "")
				throw ParseException("Element " + name + " does not have a unit (" + unit + " specified)", xe);
			val = (int)units::convert(val,xe->Attribute("unit"),unit);
		}
		return true;
	}
	
	int XMLParser::parseInt(const TiXmlElement* parent, const std::string& name, const std::string& unit, bool usedef, const int def, const std::string& attr) 
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'", parent);
		}
		int val;
		if (xe->Attribute(attr) || usedef)
			val = parseIntAttribute(xe,attr,usedef,def);
		else if ((attr == "text" || attr == "value") && xe->GetText())
			val = atoi(xe->GetText());
		else
			throw ParseException("missing '" + attr + "' attribute in element '" + name + "'", xe);
		// Unit conversion
		if (xe->Attribute("unit")) {
			if (unit == "")
				throw ParseException("Element " + name + " does not have a unit (" + unit + " specified)", xe);
			val = (int)units::convert(val,xe->Attribute("unit"),unit);
		}
		return val;		
	}
	
	bool XMLParser::parseDoubleAttribute(double& val, const TiXmlElement* xe, const std::string& attr)
	{
		int ret = xe->QueryDoubleAttribute(attr,&val);
		if (ret == TIXML_SUCCESS)
			return true;
		return false;
	}
	
	double XMLParser::parseDoubleAttribute(const TiXmlElement* xe, const std::string& attr, bool usedef, const double def)
	{
		double val;
		int ret = xe->QueryDoubleAttribute(attr,&val);
		if (ret == TIXML_WRONG_TYPE)
			throw ParseException("wrong type of value for attribute '" + attr + "' in '" + xe->Value() + "'", xe);
		else if (ret != TIXML_SUCCESS) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("no value for attribute '" + attr + "' in '" + xe->Value() + "'");
		}
		return val;		
	}
	
	bool XMLParser::parseDouble(double& val, const TiXmlElement* parent, const std::string& name, const std::string& unit, const std::string& attr)
	{
		std::string str;
		if (!parseString(str, parent, name, attr))
			return false;
		val = atof(str.c_str());
		// Unit conversion
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (xe->Attribute("unit")) {
			if (unit == "")
				throw ParseException("Element " + name + " does not have a unit (" + unit + " specified)", xe);
			val = units::convert(val,xe->Attribute("unit"),unit);
		}
		return true;
	}
	
	double XMLParser::parseDouble(const TiXmlElement* parent, const std::string& name, const std::string& unit, bool usedef, const double def, const std::string& attr) 
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'", parent);
		}
		double val;
		if (xe->Attribute(attr) || usedef)
			val = parseDoubleAttribute(xe,attr,usedef,def);
		else if ((attr == "text" || attr == "value") && xe->GetText())
			val = atof(xe->GetText());
		else
			throw ParseException("missing '" + attr + "' attribute in element '" + name + "'", xe);
		// Unit conversion
		if (xe->Attribute("unit")) {
			if (unit == "")
				throw ParseException("Element " + name + " does not have a unit (" + unit + " specified)", xe);
			val = units::convert(val,xe->Attribute("unit"),unit);
		}
		return val;		
	}
	
	osg::Vec3 XMLParser::parseVector3String(const std::string& str) 
	{
		std::string str2 = str;
		osg::Vec3 v;
		int i;
		while ((i = str2.find_first_of(",;:")) > 0)
			str2.replace(i,1," ");
		std::stringstream ss(str2);
		for (int i = 0; i < 3; i++)
			if (!(ss >> v[i]))
				throw ParseException("missing vector component");
		return v;
	}
	
	bool XMLParser::parseVector3Attribute(osg::Vec3& v, const TiXmlElement* xe, const std::string& attr)
	{
		std::string str;
		if (!parseStringAttribute(str, xe, attr))
			return false;
		v = parseVector3String(str);
		return true;
	}
	
	osg::Vec3 XMLParser::parseVector3Attribute(const TiXmlElement* xe, const std::string& attr, bool usedef, const osg::Vec3& def)
	{
		osg::Vec3 v;
		std::string str;
		if (attr == "text" && xe->GetText())
			v = parseVector3String(xe->GetText());
		else if (xe->Attribute(attr))
			v = parseVector3String(*xe->Attribute(attr));
		else if (usedef)
			v = def;
		else
			throw ParseNoElementException("Element " + std::string(xe->Value()) + " does not have a value");
		return v;
	}
	
	bool XMLParser::parseVector3(osg::Vec3& v, const TiXmlElement* parent, const std::string& name, const std::string& unit, const std::string& attr)
	{
		std::string str;
		if (!parseString(str, parent, name, attr))
			return false;
		v = parseVector3String(str);
		// Unit conversion
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (xe->Attribute("unit")) {
			if (unit == "")
				throw ParseException("Element " + name + " does not have a unit (" + xe->Attribute("unit") + " specified)", xe);
			v.x() = units::convert(v.x(),xe->Attribute("unit"),unit);
			v.y() = units::convert(v.y(),xe->Attribute("unit"),unit);
			v.z() = units::convert(v.z(),xe->Attribute("unit"),unit);
		}
		return true;		
	}
	
	osg::Vec3 XMLParser::parseVector3(const TiXmlElement* parent, const std::string& name, const std::string& unit, bool usedef, const osg::Vec3& def, const std::string& attr) 
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'", parent);
		}
		osg::Vec3 v;
		if (xe->Attribute(attr) || usedef)
			v = parseVector3Attribute(xe,attr,usedef,def);
		else if ((attr == "text" || attr == "value") && xe->GetText())
			v = parseVector3String(xe->GetText());
		else
			throw ParseException("missing '" + attr + "' attribute in element '" + name + "'", xe);
		// Unit conversion
		if (xe->Attribute("unit")) {
			if (unit == "")
				throw ParseException("Element " + name + " does not have a unit (" + xe->Attribute("unit") + " specified)", xe);
			v.x() = units::convert(v.x(),xe->Attribute("unit"),unit);
			v.y() = units::convert(v.y(),xe->Attribute("unit"),unit);
			v.z() = units::convert(v.z(),xe->Attribute("unit"),unit);
		}
		return v;
	}
	
	osg::Vec4 XMLParser::parseVector4String(const std::string& str) 
	{
		std::string str2 = str;
		osg::Vec4 v;
		int i;
		while ((i = str2.find_first_of(",;:")) > 0)
			str2.replace(i,1," ");
		std::stringstream(str2) >> v.x() >> v.y() >> v.z() >> v.w();
		return v;
	}
	
	bool XMLParser::parseVector4Attribute(osg::Vec4& v, const TiXmlElement* xe, const std::string& attr)
	{
		std::string str;
		if (!parseStringAttribute(str, xe, attr))
			return false;
		v = parseVector4String(str);
		return true;
	}
	
	osg::Vec4 XMLParser::parseVector4Attribute(const TiXmlElement* xe, const std::string& attr, bool usedef, const osg::Vec4& def)
	{
		osg::Vec4 v;
		std::string str;
		if (attr == "text" && xe->GetText())
			v = parseVector4String(xe->GetText());
		else if (xe->Attribute(attr))
			v = parseVector4String(*xe->Attribute(attr));
		else if (usedef)
			v = def;
		else
			throw ParseNoElementException("Element " + std::string(xe->Value()) + " does not have a value");
		return v;
	}
	
	bool XMLParser::parseVector4(osg::Vec4& v, const TiXmlElement* parent, const std::string& name, const std::string& unit, const std::string& attr)
	{
		std::string str;
		if (!parseString(str, parent, name, attr))
			return false;
		v = parseVector4String(str);
		// Unit conversion
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (xe->Attribute("unit")) {
			if (unit == "")
				throw ParseException("Element " + name + " does not have a unit (" + xe->Attribute("unit") + " specified)", xe);
			v.x() = units::convert(v.x(),xe->Attribute("unit"),unit);
			v.y() = units::convert(v.y(),xe->Attribute("unit"),unit);
			v.z() = units::convert(v.z(),xe->Attribute("unit"),unit);
		}
		return true;		
	}
	
	osg::Vec4 XMLParser::parseVector4(const TiXmlElement* parent, const std::string& name, const std::string& unit, bool usedef, const osg::Vec4& def, const std::string& attr) 
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'", parent);
		}
		osg::Vec4 v;
		if (xe->Attribute(attr) || usedef)
			v = parseVector4Attribute(xe,attr,usedef,def);
		else if ((attr == "text" || attr == "value") && xe->GetText())
			v = parseVector4String(xe->GetText());
		else
			throw ParseException("missing '" + attr + "' attribute in element '" + name + "'", xe);
		// Unit conversion
		if (unit != "" && xe->Attribute("unit")) {
			v.x() = units::convert(v.x(),xe->Attribute("unit"),unit);
			v.y() = units::convert(v.y(),xe->Attribute("unit"),unit);
			v.z() = units::convert(v.z(),xe->Attribute("unit"),unit);
			v.w() = units::convert(v.w(),xe->Attribute("unit"),unit);
		}
		return v;
	}
	/*
	 const Matrix3d XMLParser::parseMatrix3(TiXmlElement* parent, const std::string& name, const std::string& unit, bool usedef, const Matrix3d& def) 
	 {
	 Matrix3d M;
	 TiXmlElement* xe = parent->FirstChildElement(name);
	 if (!xe) {
	 if (usedef)
	 return def;
	 else
	 throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'");
	 }
	 std::string str;
	 if (xe->Attribute("value"))
	 str = xe->Attribute("value");
	 else if (xe->GetText())
	 str = xe->GetText();
	 else
	 throw ParseNoElementException("Element " + name + " does not have a value");
	 int i;
	 while ((i = str.find_first_of(",;:")) > 0)
	 str.replace(i,1," ");	
	 std::stringstream sin(str);
	 for (int r = 0; r < 3; r++) {
	 for (int c = 0; c < 3; c++) {
	 sin >> M(r,c);
	 // Unit conversion
	 if (xe->Attribute("unit")) {
	 if (unit == "")
	 throw ParseException("Element " + name + " does not have a unit (" + unit + " specified)");
	 M(r,c) = units::convert(M(r,c),xe->Attribute("unit"),unit);
	 }
	 }
	 }
	 return M;
	 }
	 */

	bool XMLParser::parseBooleanString(const std::string& str)
	{
		return str == "true" || str == "True" || str == "TRUE" || str == "1" || str=="on" || str == "ON";
	}
	
	bool XMLParser::parseBooleanAttribute(bool& b, const TiXmlElement* xe, const std::string& attr)
	{
		std::string str;
		if (!parseStringAttribute(str, xe, attr))
			return false;
		b = parseBooleanString(str);
		return true;
	}
	
	bool XMLParser::parseBooleanAttribute(const TiXmlElement* xe, const std::string& attr, const bool usedef, const bool def)
	{
		std::string str;
		if (attr == "text")
			str = xe->GetText();
		else if (xe->Attribute(attr))
			str = *xe->Attribute(attr);
		else if (usedef)
			return def;
		else
			throw ParseNoElementException("Element '" + std::string(xe->Value()) + "' does not have attribute '" + attr + "'");
		return parseBooleanString(str);
	}
	
	bool XMLParser::parseBoolean(bool& b, const TiXmlElement* parent, const std::string& name, const std::string& attr)
	{
		std::string str;
		if (!parseString(str, parent, name, attr))
			return false;
		b = parseBooleanString(str);
		return true;		
	}
	
	bool XMLParser::parseBoolean(const TiXmlElement* parent, const std::string& name, const bool usedef, const bool def, const std::string& attr)
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe) {
			if (usedef)
				return def;
			else
				throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'", parent);
		}
		if (xe->Attribute(attr) || usedef)
			return parseBooleanAttribute(xe,attr,usedef,def);
		else if ((attr == "text" || attr == "value") && xe->GetText())
			return parseBooleanString(xe->GetText());
		else if (usedef)
			return def;
		else
			throw ParseException("missing '" + attr + "' attribute in element '" + name + "'", xe);
	}
	
	bool XMLParser::parseVector(std::vector<double>& V, const TiXmlElement* parent, const std::string& name, const bool fixed, const std::string& unit)
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe)
			return false;
		std::string str;
		if (xe->GetText())
			str = xe->GetText();
		else {
			if (xe->Attribute("value"))
				str = xe->Attribute("value");
			else
				throw ParseException("missing text or 'value' attribute in element '" + name + "'", xe);
		}
		unsigned int i;
		while ((i = str.find_first_of(",;:")) != std::string::npos)
			str.replace(i,1," ");	
		std::stringstream sin(str);
		if (fixed) {
			for (i = 0; i < V.size(); i++) {
				if (!(sin >> V[i])) {
					std::stringstream ss;
					ss << "invalid vector length for element '" << name << "' in '" << parent->Value() << " (should be " << V.size() << ")";
					throw ParseException(ss.str());
				}
				// Unit conversion
				if (xe->Attribute("unit")) {
					if (unit == "")
						throw ParseException("Element " + name + " does not have a unit (" + xe->Attribute("unit") + " specified)", xe);
					V[i] = units::convert(V[i],xe->Attribute("unit"),unit);
				}
			}
			double d;
			if (sin >> d) {
				std::stringstream ss;
				ss << "invalid vector length for element '" << name << "' in '" << parent->Value() << " (should be " << V.size() << ")";
				throw ParseException(ss.str());
			}
		} else {
			V.clear();
			double d;
			while (sin >> d)
				V.push_back(d);
		}
		return true;
	}
	
	void XMLParser::parseTable(const TiXmlElement* parent, const std::string& name, std::vector<double>& x, std::vector<double>& y, const std::string& unit, const std::string& unit2)
	{
		const TiXmlElement* xe = parent->FirstChildElement(name);
		if (!xe) {
			throw ParseNoElementException("missing element '" + name + "' in '" + parent->Value() + "'");
		}
		std::string str;
		if (xe->Attribute("value"))
			str = xe->Attribute("value");
		else if (xe->GetText())
			str = xe->GetText();
		else
			throw ParseNoElementException("Element " + name + " does not have a value");
		int i;
		while ((i = str.find_first_of(",;:")) > 0)
			str.replace(i,1," ");	
		std::stringstream sin(str);
		double xi, yi;
		while (sin >> xi) {
			if (sin >> yi) {
				// Unit conversion
				if (xe->Attribute("unit")) {
					if (unit == "")
						throw ParseException("Element " + name + " does not have a unit (" + unit + " specified)", xe);
					x.push_back(units::convert(xi,xe->Attribute("unit"),unit));
				} else
					x.push_back(xi);
				// Unit conversion for second value
				if (xe->Attribute("unit2")) {
					if (unit2 == "")
						throw ParseException("Element " + name + " does not have a second unit (" + unit + " specified)", xe);
					y.push_back(units::convert(yi,xe->Attribute("unit2"),unit2));
				} else
					y.push_back(yi);
			} else
				throw ParseException("nonrectangular table '" + name + "' in '" + parent->Value() + "'", xe);
		}
	}
	
	std::vector<std::string> XMLParser::parseStringListAttribute(const TiXmlElement* element, const std::string& name)
	{
		std::vector<std::string> list;
		std::string str = parseStringAttribute(element,name,true,"");
		if (str.length() > 0) {
			int i;
			while ((i = str.find_first_of(",")) > 0)
				str.replace(i,1," ");
			std::stringstream ss(str);
			std::string s;
			while (ss >> s)
				list.push_back(s);
		}
		return list;
	}
	
	void XMLParser::setString(TiXmlElement* parent, const std::string& element, const std::string& value, const std::string& attr)
	{
		TiXmlElement *el = parent->FirstChildElement(element);
		if (!el) {
			el = new TiXmlElement(element);
			parent->LinkEndChild(el);
		}
		el->SetAttribute(attr, value);
	}
	
	void XMLParser::setInt(TiXmlElement* parent, const std::string& element, const int value, const std::string& attr)
	{
		std::stringstream s;
		s << value;
		setString(parent,element,s.str(),attr);
	}
	
	void XMLParser::setDouble(TiXmlElement* parent, const std::string& element, const double value, const std::string& attr)
	{
		std::stringstream s;
		s << value;
		setString(parent,element,s.str(),attr);
	}
	
	void XMLParser::setBoolean(TiXmlElement* parent, const std::string& element, const bool value, const std::string& attr)
	{
		setString(parent,element,value ? "true" : "false",attr);
	}
	
	void XMLParser::setVector3(TiXmlElement* parent, const std::string& element, const osg::Vec3& value, const std::string& attr)
	{
		std::stringstream ss;
		ss << value.x() << ", " << value.y() << ", " << value.z();
		setString(parent,element,ss.str(),attr);
	}
	
	void XMLParser::setVector4(TiXmlElement* parent, const std::string& element, const osg::Vec4& value, const std::string& attr)
	{
		std::stringstream ss;
		ss << value.x() << ", " << value.y() << ", " << value.z() << ", " << value.w();
		setString(parent,element,ss.str(),attr);
	}
	
	std::string XMLParser::currentFile = "";
	
} // namespace oge
