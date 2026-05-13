#pragma once

#include "Element.h"
#include <vector>
#include <string>

class Parser
{

private:

	void parseTagName(Element*, const std::vector<std::string>&, int, int&);
	void generateId(Element*, Element*, bool&, int&, const std::map<std::string, int>&);
	void parseAttributePart(std::string&, const std::vector<std::string>&, int, int&, char);
	void parseAttributes(Element*, const std::vector<std::string>&, int, int&, const std::map<std::string, int>&);
	void parseText(Element*, const std::vector<std::string>&, int, int&);
	void skipWhitespaces(const std::vector<std::string>&, int, int&);
	void skipTabs(const std::vector<std::string>&, int, int&);

public: 

	void parse(std::vector<Element*>&, std::vector<Element*>&, const std::vector<std::string>&, std::map<std::string, int>& );
};

