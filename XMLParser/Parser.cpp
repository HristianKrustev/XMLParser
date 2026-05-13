#include "Parser.h"

constexpr int INTOFFSET = 48;

void Parser::parseTagName(Element* elem, const std::vector<std::string>& data, int i, int& j)
{
	std::string name;
	while (data[i][j] != ' ' && data[i][j] != '>')
	{
		name += data[i][j];
		j++;
	}
	elem->setTagName(name);
}

void Parser::generateId(Element* elem, Element* parentElement, bool& isIdGenerated, int& i, const std::map<std::string, int>& idIndex)
{
	if (parentElement != nullptr)
	{
		if (idIndex.find(parentElement->getId() + "_" + char(i + INTOFFSET)) == idIndex.end())
		{
			elem->setId(parentElement->getId() + "_" + char(i + INTOFFSET));
			isIdGenerated = true;
		}
		i++;
	}
}

void Parser::parseAttributePart(std::string& attributePart, const std::vector<std::string>& data, int i, int& j, char c)
{
	while (data[i][j] != c && data[i][j] != '>')
	{
		attributePart += data[i][j];
		j++;
	}
}

void Parser::parseAttributes(Element* elem, const std::vector<std::string>& data, int i, int& j, const std::map<std::string, int>& idIndex)
{
	std::string attributeName;
	std::string attributeValue;
	bool isIdGenerated = false;
	
	while (data[i][j] != '>')
	{
		parseAttributePart(attributeName, data, i, j, '=');
		j += 2; // ="

		parseAttributePart(attributeValue, data, i, j, '"');
		j++; // "

		// CHECK TO SEE IF IT EXISTS
		if (attributeName == "id")
		{
			elem->setId(attributeValue);
			isIdGenerated = true;
		}

		if (attributeName.size() > 0 && attributeValue.size() > 0)
		{
			elem->addAttribute(attributeName, attributeValue);
		}

		if (data[i][j] == ' ')
		{
			attributeName.clear();
			attributeValue.clear();
			skipWhitespaces(data, i, j);
		}
	}

	if (!isIdGenerated)
	{
		int k = 1;
		Element* parentElement = elem->getParentElement();
		std::string currentId = parentElement->getId();
		while (!isIdGenerated)
		{
			generateId(elem, parentElement, isIdGenerated, k, idIndex);
		}
	}
}

void Parser::parseText(Element* elem, const std::vector<std::string>& data, int i, int& j)
{
	if (data[i][j] == '>') j++;

	if (data[i][j] == '\0') return;

	std::string text;
	while (data[i][j] != '<')
	{
		text += data[i][j];
		j++;
	}
	elem->setText(text);
}

void Parser::skipWhitespaces(const std::vector<std::string>& data, int i, int& j)
{
	while (data[i][j] == ' ') j++;
}

void Parser::skipTabs(const std::vector<std::string>& data, int i, int& j)
{
	while (data[i][j] == '\t') j += 4;
}


void Parser::parse(std::vector<Element*>& roots, std::vector<Element*>& elements, const std::vector<std::string>& data, std::map<std::string, int>& idIndex)
{
	bool isNextElementRoot = true;
	std::vector<Element*> newParent;
	int levelInHierarchy = 0;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 1; j < data[i].size(); j++) // parse line
		{
			skipTabs(data, i, j);
			skipWhitespaces(data, i, j);

			if (data[i][j - 1] == '<' && data[i][j] != '/' && isNextElementRoot) // newRoot
			{
				levelInHierarchy = 0;
				Element* elem = new Element();

				//j++; // <
				parseTagName(elem, data, i, j);
				skipWhitespaces(data, i, j);
				parseAttributes(elem, data, i, j, idIndex);
				parseText(elem, data, i, j);

				roots.push_back(elem);
				elements.push_back(elem);
				newParent.push_back(elem);
				idIndex.emplace(elem->getId(), elements.size() - 1);
				isNextElementRoot = false;

			}
			else if (data[i][j - 1] == '<' && data[i][j] != '/') // newChild
			{
				levelInHierarchy++;
				Element* elem = new Element();

				// j++; // <
				elem->setParentElement(*newParent.back());
				parseTagName(elem, data, i, j);
				skipWhitespaces(data, i, j);
				parseAttributes(elem, data, i, j, idIndex);
				parseText(elem, data, i, j);
				newParent.back()->addChild(*elem);

				elements.push_back(elem);
				newParent.push_back(elem);
				idIndex.emplace(elem->getId(), elements.size() - 1);
			}
			else if (data[i][j - 1] == '<' && data[i][j] == '/') // closeTag
			{
				if (--levelInHierarchy < 0) isNextElementRoot = true;
				newParent.pop_back();
				break;
			}
		}
	}
}
