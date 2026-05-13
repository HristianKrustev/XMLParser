#include "Element.h"

constexpr int INDENTATION_SPACE = 2;

void Element::copy(const Element& other)
{
	tagName = other.tagName;
	id = other.id;
	text = other.text;
	parentElement = other.parentElement;
	levelInHierarchy = other.levelInHierarchy;
	attributes = other.attributes;

	for (int i = 0; i < other.children.size(); i++)
	{
		children.push_back(new Element(*other.children[i]));
	}
}

void Element::free()
{
	tagName = "";
	id = "";
	text = "";
	parentElement = nullptr;
	levelInHierarchy = 0;
	attributes.clear();
	
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
}

void Element::writeIndentationToStream(std::ostream& os) const
{
	for (int i = 0; i < INDENTATION_SPACE * levelInHierarchy; i++)
	{
		os << ' ';
	}
}

void Element::writeOpeningTagToStream(std::ostream& os) const
{
	os << '<';
	os << getTagName();
	writeAttributesToStream(os);
	os << '>';
}

void Element::writeAttributesToStream(std::ostream& os) const
{
	for (auto i = attributes.begin(); i != attributes.end(); i++)
	{
		os << ' ' << i->first << '=' << '"' << i->second << '"';
	}
}

void Element::writeTextToStream(std::ostream& os) const
{
	os << getText();
}

void Element::writeChildrenToStream(std::ostream& os) const
{
	if (!children.empty())
	{
		os << std::endl;
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->writeToStream(os);
		}
	}
}

void Element::writeClosingTagToStream(std::ostream& os) const
{
	os << "</";
	os << getTagName();
	os << '>';
	os << std::endl;
}

Element::Element()
{
	tagName = "";
	id = "";
	text = "";
	parentElement = nullptr;
	levelInHierarchy = 0;
	attributes.clear();
	children.clear();
}

Element::Element(const Element& other)
{
	copy(other);
}

Element& Element::operator=(const Element& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

Element::~Element()
{
	free();
}

std::string Element::getTagName() const
{
	return tagName;
}

void Element::setTagName(const std::string& tagName)
{
	this->tagName = tagName;
}

std::string Element::getId() const
{
	return id;
}

void Element::setId(const std::string& id)
{
	this->id = id;
}

std::string Element::getText() const
{
	return text;
}

void Element::setText(const std::string& text)
{
	this->text = text;
}

int Element::getLevelInHierarchy() const
{
	return levelInHierarchy;
}

Element* Element::getParentElement() const
{
	return parentElement;
}

void Element::setParentElement(Element& parentElement)
{
	this->parentElement = &parentElement;
	levelInHierarchy = parentElement.getLevelInHierarchy() + 1;
}

void Element::writeToStream(std::ostream& os) const
{
	writeIndentationToStream(os);
	writeOpeningTagToStream(os);
	writeTextToStream(os);
	writeChildrenToStream(os);
	// ADD INDETATION TO CLOSING TAG
	writeClosingTagToStream(os);
}

void Element::addAttribute(const std::string& name, const std::string& value)
{
	attributes.emplace(name, value);
}

void Element::addChild(Element& child)
{
	children.push_back(&child);
}

void Element::removeAttribute(const std::string& name)
{
	attributes.erase(name);
}

void Element::removeChild(int position)
{
	children.erase(children.begin() + position);
}