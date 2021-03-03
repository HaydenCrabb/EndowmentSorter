#pragma once
#ifndef Student_h
#define Student_h
#include "Student.h"

Student::Student() {
	info = new DoubleyLinkedList<std::string>;
	values = new DoubleyLinkedList<Solution>;
};
Student::~Student() {
	delete info;
	delete values;
}
#endif