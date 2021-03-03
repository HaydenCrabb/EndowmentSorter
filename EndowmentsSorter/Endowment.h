#pragma once
#ifndef ENDOWMENT_H
#define ENDOWMENT_H

#include <string>
#include "DoubleyLinkedList.h"
#include "Requirement.h"

struct info {
	std::string title;
	std::string data;
};

class Endowment
{
public:
	inline Endowment();
	inline ~Endowment();

	//I want to use linked lists. 
	DoubleyLinkedList<info>* information;
	DoubleyLinkedList<Requirement>* requirements;

	//potentially store the number of potential students in this array.
	int potentialStudents;

};

#endif