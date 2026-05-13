#include "Document.h"
#include <fstream>
#include <iostream>

void Document::saveAt(const std::string& path)
{
	std::ofstream ofile(path, std::ios::out);

	for (int i = 0; i < roots.size(); i++)
	{
		roots[i]->writeToStream(ofile);
	}

	ofile.close();
}

void Document::setFileName(const std::string& path)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
		{
			fileName.clear();
			continue;
		}

		fileName += path[i];
	}
}

void Document::open(const std::string& path)
{
	if (isLoaded) close();

	std::ifstream ifile(path, std::ios::in);

	if (!ifile.is_open())
	{
		std::ofstream ofile(path, std::ios::out);
		ofile.close();

		ifile.open(path, std::ios::in);
	}

	if (!ifile.is_open()) throw std::runtime_error("Cannot open file");

	this->path = path;
	setFileName(path);
	isLoaded = true;

	char line[1025];

	while (ifile.getline(line, 1025))
	{
		rawData.push_back(line);
	}

	Parser parser;
	parser.parse(roots, allElements, rawData, idIndex);

	ifile.close();

	std::cout << "Successfully opened " << fileName << std::endl;
}

void Document::close()
{
	if (!isLoaded)
	{
		std::cout << "Open a file first! \n";
		return;
	}

	path.clear();
	rawData.clear();
	roots.clear();
	allElements.clear();
	idIndex.clear();
	isLoaded = false;

	std::cout << "Successfully closed " << fileName << std::endl;

	fileName.clear();
}

void Document::save()
{
	if (!isLoaded)
	{
		std::cout << "Open a file first! \n";
		return;
	}

	saveAt(path);

	std::cout << "Successfully saved " << fileName << std::endl;
}

void Document::saveAs(const std::string& newPath)
{
	if (!isLoaded)
	{
		std::cout << "Open a file first! \n";
		return;
	}

	saveAt(newPath);
	this->path = newPath;
	setFileName(path);

	std::cout << "Successfully saved " << fileName << std::endl;
}

void Document::help()
{
	std::cout << "The following commands are supported: \n"
		<< "open <file>	opens <file> \n"
		<< "close			closes currently opened file \n"
		<< "save			saves the currently open file \n"
		<< "saveAs <file>	saves the currently open file in <file> \n"
		<< "help			prints this information \n"
		<< "exit			exists the program \n";
}

void Document::exit()
{
	std::cout << "Exiting the program";
	std::exit(0);
}

void Document::print()
{
	for (int i = 0; i < roots.size(); i++)
	{
		roots[i]->writeToStream(std::cout);
	}
}

int main()
{
	Document doc;
	doc.open("C:\\XMLParser\\XMLParser\\XMLParser\\test.txt");
	doc.print();
	doc.save();
	doc.close();
}
