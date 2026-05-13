#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Element.h"
#include "Parser.h"

class Document
{

private:

	std::string path;
	std::string fileName;
	bool isLoaded = false;

	std::vector<std::string> rawData;
	std::vector<Element*> roots; // FREE
	std::vector<Element*> allElements; // FREE 
	//maps an element's unique id to it's index in the vector allElements
	std::map<std::string, int> idIndex;

	void saveAt(const std::string& path);
	void setFileName(const std::string& path);

public:

	void open(const std::string& path);
	void close();
	void save();
	void saveAs(const std::string& newPath);
	void help();
	void exit();
	void print();
};

