/*
* XMLCatalogParser.h
*
* Created on: Jul 31, 2014
* Author: Hvarnah
*/

#ifndef XMLCATALOGPARSER_H_
#define XMLCATALOGPARSER_H_

namespace GL_test 
{

/**
 * the class XMLCatalogParser reads a catalog from xml formatted stream and writes a table in html formatted stream
 */
class XMLCatalogParser 
{
public:
	typedef std::vector<std::vector<std::string> > CatalogType;

	/**
	 * readXML reads the xml formatted stream and stores catalog items in the object 
	 */
	void readXML(std::istream& inputStream);

	/**
	 * writeHTML writes the html table from inner data in outputStream
	 */
	void writeHTML(std::ostream& outputStream) const;

	/**
	 * setXMLStructure sets up catalog parameters and is neccessary to be invoked before readXML
	 */
	void setXMLStructure(const std::string& catalogName, const std::string& itemName,  const std::vector<std::string> & properties, const std::vector<std::string> & columnTitles);

	/**
	 * setTableStyle sets up the style of the table different from defaults
	 */
	void setTableStyle(const std::string & titleColor, const std::string & rowColorEven, const std::string & rowColorOdd, const std::string & tableStyle, const std::string & titleStyle);

	/**
	 * setIndent sets up a string that is put in stream before each line. It must be several tabs or spaces
	 */
	void setIndent(const std::string & indent);

	XMLCatalogParser();
	~XMLCatalogParser();

private:
	//all private stuff is hidden in cpp
	class XMLCatalogParserImpl;
	XMLCatalogParserImpl * m;
};

} /* namespace GL_test */

#endif /* XMLCATALOGPARSER_H_ */
