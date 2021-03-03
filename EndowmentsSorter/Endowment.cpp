#pragma once
#ifndef Endowment_h
#define Endowment_h
#include "Endowment.h"

Endowment::Endowment() {
	information = new DoubleyLinkedList<info>;
	requirements = new DoubleyLinkedList<Requirement>;
	potentialStudents = 0;
}

Endowment::~Endowment() {
		delete information;
		delete requirements;
}
#endif