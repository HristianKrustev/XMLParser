#include "Parser.h"

void Parser::parse(std::vector<Element*>& elements, const std::vector<std::string>& data)
{
	bool isNextElementRoot = true;
	std::vector<Element*> newParent;
	int levelInHierarchy = 0;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++) // parse line
		{
			if (data[i][j] == '<' && data[i][j + 1] != '/' && isNextElementRoot) // newRoot
			{
				levelInHierarchy = 0;
				Element* elem = new Element();
				// add elem properties here

				elements.push_back(elem);

				isNextElementRoot = false;
				newParent.push_back(elem);

			}
			else if (data[i][j] == '<' && data[i][j + 1] != '/') // newChild
			{
				levelInHierarchy++;
				Element* elem = new Element();
				// add elem properties here 

				elements.push_back(elem);
				newParent.back()->addChild(*elem);


				newParent.push_back(elem);
			}
			else if (data[i][j] == '<' && data[i][j + 1] == '/') // closeTag
			{
				if (--levelInHierarchy < 0) isNextElementRoot = true;
				// pop newParent
			}
		}
	}
}
