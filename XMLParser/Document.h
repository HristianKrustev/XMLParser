#pragma once

#include <vector>
#include <string>
#include <map>
#include "Element.h"

class Document
{

private:

	std::string fileName;
	bool isLoaded = false;

	std::vector<Element*> allElements;
	std::map<std::string, Element*> idIndex;

public:

	void open(const std::string& fileName);
	void close();
	void save();
	void saveAs(const std::string& newFileName);
	void help();
	void exit();
};

