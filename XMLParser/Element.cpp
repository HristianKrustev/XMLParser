#include "Element.h"

Element::Element(const std::string& tagName)
{
	this->tagName = tagName;
	id = "";
	text = "";
	parentElement = nullptr;
	levelInHierarchy = 0;
}

Element::Element(const std::string& tagName, const std::string& id, const std::string& text)
{
	this->tagName = tagName;
	this->id = id;
	this->text = text;
	parentElement = nullptr;
	levelInHierarchy = 0;
}

Element::Element(const std::string& tagName, const std::string& id, const std::string& text, const Element& parentElement)
{
	this->tagName = tagName;
	this->id = id;
	this->text = text;
	this->parentElement = &parentElement;
	levelInHierarchy = parentElement.levelInHierarchy + 1;
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

const Element& Element::getParentElement() const
{
	return *parentElement;
}

void Element::setParentElement(const Element& parentElement)
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