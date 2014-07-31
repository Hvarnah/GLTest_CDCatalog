/*
* main.cpp
*
* Created on: Jul 31, 2014
* Author: Hvarnah
*
* This is the main file of GlobalLogic test application. It represents the example of using the XMLCatalogParser class. 
* 
* The developed functionality that is contained in XMLCatalogParser class gives the possibility to put a table with html formatting in a stream. 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <XMLCatalogParser.h>

#define el_sizeof(a) (sizeof(a) / sizeof(a[0]))

using namespace std;
using namespace GL_test;

const char * cdProperties[] = {"TITLE", "ARTIST", "COUNTRY", "COMPANY", "PRICE", "YEAR"};
const char * columnTitles[] = {"Title", "Artist", "Country", "Company", "Price", "Year"};

enum ReturnCodes {RC_SUCCESS, RC_WRONG_PARAM, RC_FILE_ERROR, RC_XML_ERROR, RC_ERROR};

/**
 * main function can receive 1 (default) or 3 arguments. First is a path to the application. 
 * Two other are name of input and output file. All other cases causes an error.
 */
int main(int argc, char* argv[])
{
	string inputFileName, outputFileName;

	if (argc == 1)
	{
		cout << "Enter input file name >";
		cin >> inputFileName;

		cout << "Enter output file name >";
		cin >> outputFileName;
	}
	else if (argc == 3)
	{
		inputFileName = argv[1];
		outputFileName = argv[2];
	}
	else 
	{
		cout << "wrong input parameters\n";
		return RC_WRONG_PARAM;
	}

	ifstream inFile(inputFileName);
	ofstream outFile(outputFileName);

	if (inFile.fail() || outFile.fail())
	{
		cout << "Unable to open the files\n";
		return RC_FILE_ERROR;
	}

	XMLCatalogParser parser;

	parser.setXMLStructure(	"CATALOG", 
							"CD", 
							vector<string>(cdProperties, cdProperties + el_sizeof(cdProperties)), 
							vector<string>(columnTitles, columnTitles + el_sizeof(columnTitles))
							);

	parser.setIndent("		");

	try
	{
		parser.readXML(inFile);

		outFile <<	"<!DOCTYPE HTML>\n"
					"<html>\n"
					"	<head>\n"
					"		<title>CD Catalog</title>\n"
					"	</head>\n"
					"	<body>\n";


		parser.writeHTML(outFile);
	
		outFile <<	"	</body>\n"
					"</html>\n";
	}
	catch(string er)
	{
		cout << er;
		return RC_XML_ERROR;
	}
	catch(...)
	{
		cout << "An error occured";
		return RC_ERROR;
	}

	return RC_SUCCESS;
}
