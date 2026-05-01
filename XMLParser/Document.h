#pragma once

#include <vector>
#include <string>
#include <map>
#include "Element.h"

class Document
{

private:

	std::string path;
	bool isLoaded = false;

	std::vector<std::string> rawData;
	std::vector<Element*> allElements;
	//maps an element's unique id to it's index in the vector allElements
	std::map<std::string, Element*> idIndex;

public:

	void open(const std::string& path);
	void close();
	void save();
	void saveAs(const std::string& newPath);
	void help();
	void exit();
};

