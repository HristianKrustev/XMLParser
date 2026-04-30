#pragma once

#include <string>
#include <map>
#include <vector>

class Element
{

private:

	std::string	tagName;
	std::string id;
	std::string text;

	int levelInHierarchy;
	const Element* parentElement;

	std::map<std::string, std::string> attributes;
	std::vector<Element*> children;

public:

	Element(const std::string&);
	Element(const std::string&, const std::string&, const std::string&);
	Element(const std::string&, const std::string&, const std::string&, const Element&);

	std::string getTagName() const;
	void setTagName(const std::string&);

	std::string getId() const;
	void setId(const std::string&);

	std::string getText() const;
	void setText(const std::string&);

	int getLevelInHierarchy() const;
	const Element& getParentElement() const;
	void setParentElement(const Element&);

	void addAttribute(const std::string&, const std::string&);
	void addChild(Element&);
	void removeAttribute(const std::string&);
	void removeChild(int);
};

