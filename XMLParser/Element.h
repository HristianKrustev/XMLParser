#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Element
{

private:

	std::string	tagName;
	std::string id;
	std::string text;

	int levelInHierarchy;
	Element* parentElement;

	std::map<std::string, std::string> attributes;
	std::vector<Element*> children; // FREE

	void copy(const Element&);
	void free();

	void writeIndentationToStream(std::ostream&) const;
	void writeOpeningTagToStream(std::ostream&) const;
	void writeAttributesToStream(std::ostream&) const;
	void writeTextToStream(std::ostream&) const;
	void writeChildrenToStream(std::ostream&) const;
	void writeClosingTagToStream(std::ostream&) const;

public:

	Element();
	Element(const Element&);
	Element& operator=(const Element&);
	~Element();

	std::string getTagName() const;
	void setTagName(const std::string&);

	std::string getId() const;
	void setId(const std::string&);

	std::string getText() const;
	void setText(const std::string&);

	int getLevelInHierarchy() const;
	Element* getParentElement() const;
	void setParentElement(Element&);

	void writeToStream(std::ostream&) const;

	void addAttribute(const std::string&, const std::string&);
	void addChild(Element&);
	void removeAttribute(const std::string&);
	void removeChild(int);
};

