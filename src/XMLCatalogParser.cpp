/*
* XMLCatalogParser.cpp
*
* Created on: Jul 31, 2014
* Author: Hvarnah
*/

#include <iostream>
#include <vector>
#include <string>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/assign/std/vector.hpp>

#include "XMLCatalogParser.h"

using namespace std;
using namespace boost::property_tree;
using namespace boost::assign;

namespace GL_test 
{

class XMLCatalogParser::XMLCatalogParserImpl
{
public:
	XMLCatalogParser::CatalogType mCatalog;

	std::string mCatalogName;
	std::string mItemName;

	std::vector<std::string> mProperties;
	std::vector<std::string> mColumnTitles;

	std::vector<std::string> mRowColors;
	std::string mTitleColor;
	std::string mIndent;
	std::string mTableStyle;;
	std::string mTitleStyle;

	XMLCatalogParserImpl():
		mTitleColor("BBFFBB"),
		mTableStyle("border=\"1\""),
		mTitleStyle("align=\"center\"; style=\"font-weight: bold; font-size: 14pt\"")
	{
		mRowColors += "FFFFDD", "FFFFBB";
	}
};

XMLCatalogParser::XMLCatalogParser():
	m(new XMLCatalogParserImpl())
{
}

XMLCatalogParser::~XMLCatalogParser()
{
	delete m;
}

void XMLCatalogParser::readXML(istream& inputStream)
{
	// the xml data is stored into property tree using boost  
	// and then is transferred to string arrays.
	try
	{
		ptree pt;
		read_xml(inputStream, pt);
		m->mCatalog.clear();

		for (ptree::iterator & it = pt.get_child(m->mCatalogName).begin(); it != pt.get_child(m->mCatalogName).end(); it++) 
		{
			if(it->first == m->mItemName) 
			{
				vector<string> item;
				item.resize(m->mProperties.size());

				for (int i = 0; i < m->mProperties.size(); ++i)
					item[i] = it->second.get<string>(m->mProperties[i]);

				m->mCatalog.push_back(item);
			}
		}
	}
	catch(xml_parser_error er)
	{
		throw("xml reading failed: "+er.message());
	}
	catch(ptree_bad_data er)
	{
		throw(string("wrong xml structure"));
	}
	catch(ptree_bad_path er)
	{
		throw(string("wrong xml structure"));
	}
	catch(...)
	{
		throw;
	}
}

void XMLCatalogParser::writeHTML(ostream& outputStream) const
{
	// a manual method was chosen for output as the most optimal. No boost here.
	try
	{
		outputStream	<< m->mIndent <<	"<table " << m->mTableStyle << ">\n" 
						<< m->mIndent <<	"	<tr bgcolor = " << m->mTitleColor << "; " << m->mTitleStyle << ">\n";

		for (vector<string>::const_iterator title = m->mColumnTitles.begin(); title != m->mColumnTitles.end(); ++title)
			outputStream << m->mIndent <<"		<td>" << *title << "</td>\n";

		outputStream << m->mIndent << "	</tr>\n";
	
		int col = 0;

		for (CatalogType::const_iterator item = m->mCatalog.begin(); item != m->mCatalog.end(); ++item)
		{
			outputStream << m->mIndent << "	<tr bgcolor = \""<<m->mRowColors[(col++)%2]<<"\">\n";

			for (vector<string>::const_iterator param = item->begin(); param != item->end(); ++param)
				outputStream << m->mIndent <<"		<td>" << *param << "</td>\n";
		
			outputStream << m->mIndent << "	</tr>\n";
		}
	
		outputStream << m->mIndent << "</table>\n";
	}
	catch(...)
	{
		throw(string("html writing failed"));
	}
}


void XMLCatalogParser::setXMLStructure(const string& catalogName, const string& itemName,  const vector<string> & properties, const vector<string> & columnTitles)
{
	m->mCatalogName = catalogName;
	m->mItemName = itemName;
	m->mProperties = properties;
	m->mColumnTitles = columnTitles;
}

void XMLCatalogParser::setTableStyle(const string & titleColor, const string & rowColorEven, const string & rowColorOdd, const string & tableStyle, const string & titleStyle)
{
	m->mTitleColor = titleColor; 
	m->mRowColors[0] = rowColorEven;
	m->mRowColors[1] = rowColorOdd;
	m->mTableStyle = tableStyle;
	m->mTitleStyle = titleStyle;
}

void XMLCatalogParser::setIndent(const std::string & indent)
{
	m->mIndent = indent;
}

} /* namespace GL_test */
