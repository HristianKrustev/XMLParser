#include "Element.h"

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

Element::Element()
{
	tagName = tagName;
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