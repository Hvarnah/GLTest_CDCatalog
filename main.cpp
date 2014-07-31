// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "XMLCatalogParser.h"

#define el_sizeof(a) (sizeof(a) / sizeof(a[0]))

using namespace std;
using namespace GL_test;

const char * cdProperties[] = {"TITLE", "ARTIST", "COUNTRY", "COMPANY", "PRICE", "YEAR"};
const char * columnTitles[] = {"Title", "Artist", "Country", "Company", "Price", "Year"};


enum ReturnCodes {RC_SUCCESS, RC_WRONG_PARAM, RC_FILE_ERROR};

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

	vector<string> cdPropertiesV(cdProperties, cdProperties + sizeof(cdProperties) / sizeof(cdProperties[0]));
	vector<string> titlesV(columnTitles, columnTitles + sizeof(columnTitles) / sizeof(columnTitles[0]));

	parser.setXMLStructure(	"CATALOG", 
							"CD", 
							vector<string>(cdProperties, cdProperties + el_sizeof(cdProperties)), 
							vector<string>(columnTitles, columnTitles + el_sizeof(columnTitles))
							);

	parser.setIndent("		");

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

	return RC_SUCCESS;
}
