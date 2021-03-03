#pragma once
#ifndef REQUIREMENT_H
#define REQUIREMENT_H


class Requirement {
public:
	Requirement();
	~Requirement();

    //getem
    int getFailures();

    //setters
    void createListOfStrings(std::string);
    void setGreaterThanValue(double);
    void setTitle(std::string);
    void causedFailure();

    //checkem.
    bool isGreaterThan(double);
    bool containsString(std::string);

private:
	std::string title;
    int causedFailures; // an integer which counts the number of times this attribute caused a student to not get a scholarship.
	double greater_than;     //the value the student needs to be greater than or equal to in order to match. 
	//bool has_value; We don't need a variable, if the attribute is of type 2, then we know what to do. If the cell has a value it matches with this endowment, otherwise no. The requirements array does not need to be consulted.
	std::string* list_of_strings; // a list of strings which the student needs to have one of in order ot match. 
    int array_size;
};

#endif