#pragma once
#ifndef Attribute_h
#define Attribute_h
#include <string>


class Attribute
{
public:
	Attribute();
	~Attribute();
	std::string getTitle();
	int getId();
	int getType();

	void setId(int);
	void setTitle(std::string);
	void setType(int);


private:
	int type; 
	std::string title;	//The name of this attribute. Ex. Estimated Need, Outside Activities, etc.
	int id;			//an integer which shows which bit of student info this attribute will be compared to. 

};
#endif