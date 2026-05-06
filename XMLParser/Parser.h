#pragma once

#include "Element.h"
#include <vector>
#include <string>

class Parser
{

private:

	void parseTagName(Element*, const std::vector<std::string>&, int, int&);
	void parseAttributePart(std::string&, const std::vector<std::string>&, int, int&, char);
	void parseAttributes(Element*, const std::vector<std::string>&, int, int&);
	void parseText(Element*, const std::vector<std::string>&, int, int&);
	void skipWhitespaces(const std::vector<std::string>&, int, int&);

public: 

	void parse(std::vector<Element*>&, const std::vector<std::string>&);
};

