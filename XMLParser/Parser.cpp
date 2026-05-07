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

void Parser::generateId(Element* elem, bool& isIdGenerated, int& i, const std::map<std::string, int>& idIndex)
{
	if (elem->getParentElement() != nullptr)
	{
		if (idIndex.find(elem->getParentElement()->getId() + "_" + char(i + INTOFFSET)) != idIndex.end())
		{
			elem->setId(elem->getParentElement()->getId() + "_" + char(i + INTOFFSET));
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

	int k = 1;
	while (!isIdGenerated)
	{
		generateId(elem, isIdGenerated, k, idIndex);
	}
}

void Parser::parseText(Element* elem, const std::vector<std::string>& data, int i, int& j)
{
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

void Parser::parse(std::vector<Element*>& elements, const std::vector<std::string>& data, std::map<std::string, int>& idIndex)
{
	bool isNextElementRoot = true;
	std::vector<Element*> newParent;
	int levelInHierarchy = 0;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++) // parse line
		{
			skipWhitespaces(data, i, j);

			if (data[i][j] == '<' && data[i][j + 1] != '/' && isNextElementRoot) // newRoot
			{
				levelInHierarchy = 0;
				Element* elem = new Element();

				j++; // <
				parseTagName(elem, data, i, j);
				skipWhitespaces(data, i, j);
				parseAttributes(elem, data, i, j, idIndex);
				parseText(elem, data, i, j);

				elements.push_back(elem);
				newParent.push_back(elem);
				idIndex.emplace(elem->getId(), elements.size() - 1);
				isNextElementRoot = false;

			}
			else if (data[i][j] == '<' && data[i][j + 1] != '/') // newChild
			{
				levelInHierarchy++;
				Element* elem = new Element();

				j++; // <
				parseTagName(elem, data, i, j);
				skipWhitespaces(data, i, j);
				parseAttributes(elem, data, i, j, idIndex);
				parseText(elem, data, i, j);
				elem->setParentElement(*newParent.back());
				newParent.back()->addChild(*elem);

				elements.push_back(elem);
				newParent.push_back(elem);
				idIndex.emplace(elem->getId(), elements.size() - 1);
			}
			else if (data[i][j] == '<' && data[i][j + 1] == '/') // closeTag
			{
				if (--levelInHierarchy < 0) isNextElementRoot = true;
				newParent.pop_back();
			}
		}
	}
}
