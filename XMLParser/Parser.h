#pragma once

#include "Element.h"
#include <vector>
#include <string>

class Parser
{

private:

	void parseElement(std::vector<Element*>, const std::string&);
	void parseTagName(std::string&, const std::string&);
	void parseAttributes(std::map<std::string, std::string>&, const std::string&);
	void parseText(std::string, const std::string&);

public: 

	void parse(std::vector<Element*>&, const std::vector<std::string>&);
};

