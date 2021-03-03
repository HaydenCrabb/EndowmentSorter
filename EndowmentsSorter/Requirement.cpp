#include <string>
#include <sstream> 
#include <iostream>
#include "Requirement.h"

using namespace std;

int Requirement::getFailures()
{
    return causedFailures;
}
void Requirement::setTitle(string new_title)
{
    title = new_title;
}
void Requirement::causedFailure()
{
    causedFailures++;
}
int getArraySize(string input)
{
    int long numberOfOccurences = count(input.begin(), input.end(), '|') + 1;
    return static_cast<int>(numberOfOccurences);
}
string stripSpaces(string input)
{
    string newString = input;
    int count = 0;
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] != ' ' && input[i] != '"') // only copy over characters which are not spaces.
        {
            newString[count++] = input[i]; // post fix increment
        }
    }
    newString.resize(count);
    return newString;
}
string toUpperCase(string input)
{
    string newString = input;
    for (size_t i = 0; i < input.length(); i++) {
        newString[i] = toupper(input[i]);
    }
    return newString;
}
string processString(string input)
{
    string newString = toUpperCase(input);
    newString = stripSpaces(newString);
    return newString;
}
void splitByCharacters(string* array, string input, bool replaceBlanksWithAny)
{
    //Often times a colum has multiple options. Therefore the string in that colum will have a string with pipe characters, something like this: FR|SO|SR Meaning Freshmen sophmores, or Seniors. We need to seperate these into an array. Arrays are passed by reference, so no need to return them.
    string cleanString = processString(input);
    if (cleanString == "" && replaceBlanksWithAny)
    {
        cleanString = "ANY";
    }
    stringstream ssin(cleanString);
    string item;
    int i = 0;
    while (getline(ssin, item, '|'))
    {
        if (item != "")
        {
            array[i] = item;
            i++;
        }
    }
}

Requirement::Requirement()
{
    title = "";
    list_of_strings = nullptr;
}
Requirement::~Requirement()
{
    if (list_of_strings != nullptr)
    {
        delete list_of_strings;
    }
}
void Requirement::createListOfStrings(string input)
{
    array_size = getArraySize(input);
    list_of_strings = new string[array_size];
    splitByCharacters(list_of_strings, input, true);
}
bool Requirement::isGreaterThan(double test_value)
{
    return (greater_than >= test_value ? true : false);
}
void Requirement::setGreaterThanValue(double new_value)
{
    greater_than = new_value;
}
bool Requirement::containsString(string test_string)
{
    string acceptableAnswer = "ANY";
    //the function used to test if the values match for a student and a Endowment.
    if (test_string != "")
    {
        for (int i = 0; i < array_size; i++)
        {
            if (test_string.find(*(list_of_strings + i)) != string::npos || (list_of_strings + i)->find(test_string) != string::npos || *(list_of_strings + i) == acceptableAnswer)
            {
                return true;
            }
        }
    }
    return false;
}