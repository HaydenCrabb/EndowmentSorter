#pragma once
#include "Attribute.h"


Attribute::Attribute()
{
	type = 0;
	title = "";
	id = NULL;
}
std::string Attribute::getTitle()
{
	return title;
}
int Attribute::getId()
{
	return id;
}
void Attribute::setTitle(std::string newTitle)
{
	title = newTitle;
}
void Attribute::setId(int newId)
{
	id = newId;
}
void Attribute::setType(int newType)
{
	// 0 - list_of_strings
	// 1 - greater than or equal to.
	// 2 - has value;
	// 3 - INFORMATION
	if (newType >= 0 && newType <= 3)
	{
		type = newType;
	}
	else {
		type = 0;
	}
}
int Attribute::getType()
{
	return type;
}
Attribute::~Attribute()
{
	//decontstructer
	//nothing to do here.
}