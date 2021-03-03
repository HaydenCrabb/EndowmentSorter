#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "DoubleyLinkedList.h"


struct Solution {
	//this struct allows the values a student possesses to be multiple different types depending on what the attribute is asking for. 
	double double_value;
	std::string string_value;
	bool has_value;
};

class Student {
public:
	Student();
	~Student();

	DoubleyLinkedList<std::string> * info;
	DoubleyLinkedList<Solution> * values;
};
#endif