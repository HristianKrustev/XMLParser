#include "Document.h"
#include <fstream>
#include <iostream>

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

	if (!ifile) throw std::runtime_error("Cannot open file");

	isLoaded = true;

	char line[1025];

	while (ifile.getline(line, 1025))
	{
		rawData.push_back(line);
	}

	// PARSE HERE

	ifile.close();

	std::cout << "Successfully opened " << path;
}

void Document::close()
{
	// DELETE DATA HERE

	isLoaded = false;

	std::cout << "Successfully closed " << path;
}

void Document::save()
{
	std::ofstream ofile(path, std::ios::out);

	// SAVE LOGIC

	ofile.close();
}

void Document::saveAs(const std::string& newPath)
{
	std::ofstream ofile(newPath, std::ios::out);

	// SAVE LOGIC

	ofile.close();
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
	return;
}

int main()
{
	Document d;
	d.open("sad.txt");
}