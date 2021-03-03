#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Endowment.h"
#include "DoubleyLinkedList.h"
#include "Student.h"
#include "Attribute.h"

using namespace std;


//the global variables where all our endowments and student values will be stored.
DoubleyLinkedList<Endowment> * all_endowments;
DoubleyLinkedList<Student> * all_students;

//the global list of all attributes 
DoubleyLinkedList<Attribute> * all_attributes;

void csvParser(string input, string* array, int arraySize)
{
    bool isEncapsulated = false;
    int previousSplit = 0;
    int arrayCounter = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (arrayCounter < arraySize)
        {
            if (input[i] == '"')
            {
                isEncapsulated = !isEncapsulated;
            }
            if (input[i] == ',' && isEncapsulated == false)
            {
                //split into array
                if (previousSplit != i)
                {
                    array[arrayCounter] = input.substr(previousSplit, i - previousSplit);
                    arrayCounter++;
                    previousSplit = i + 1;
                }
                else
                {
                    array[arrayCounter] = "";
                    arrayCounter++;
                    previousSplit++;
                }
            }
            if ((i == input.length() - 1) && (input[i] != ','))
            {
                array[arrayCounter] = input.substr(previousSplit, i - previousSplit);
            }
        }
    }
}

void inputEndowmentsData(ifstream& infile, bool firstline)
{
    int number_of_rows = 400; // this number has to be precise. I need to determine it. 
    int number_of_columns = 26; //this number has to be precise. Must be determined
    int row_position = 0;                
    string holder_variable;
    string all_cells_in_string[26];
    if (firstline == false) // if we are not reading in the first line, then skip it. 
    {
        getline(infile, holder_variable);
        holder_variable = "";
    }
    while (infile.good() && row_position < number_of_rows)
    {
        getline(infile, holder_variable);
        csvParser(holder_variable, all_cells_in_string, number_of_columns);
        if (firstline)
        {
            //iterate over every attribute on this line
            for (int i = 0; i < number_of_columns; i++)
            {
                Attribute next_element;
                next_element.setId(i);
                next_element.setTitle(all_cells_in_string[i]);
                all_attributes->append(next_element);
            }
            break;
        }
        else {
            //create a new endowment to be added to the endowments dll
            Endowment new_endowment;
            //iterate through the attributes array and add items here. 
            int i = 0; // a variable to track where we are in the line as compared to the attributes arrray.
            DLLNode<Attribute>* tempAttribute;
            tempAttribute = nullptr;
            all_attributes->getNextNode(tempAttribute);
            while (tempAttribute != nullptr)
            {
                //do the stuffs.
                Requirement next_requirement; // requirement to be appended to the all_endowments list
                if (tempAttribute->info.getType() == 0)
                {
                    //it's a list of strings.
                    next_requirement.setTitle(tempAttribute->info.getTitle());
                    next_requirement.createListOfStrings(all_cells_in_string[i]);
                }
                else if (tempAttribute->info.getType() == 1)
                {
                    //its a greater than-
                    next_requirement.setTitle(tempAttribute->info.getTitle());
                    //next_requirement.setGreaterThanValue()
                }
                else if (tempAttribute->info.getType() == 2)
                {
                    //its a has_value

                }
                else if (tempAttribute->info.getType() == 3)
                {
                    //its information
                    //special case where we will have to create an information struct and appended it to the all_endowments 
                    info newInfo;
                    newInfo.title = tempAttribute->info.getTitle();
                    newInfo.data = all_cells_in_string[i];
                    new_endowment.information->append(newInfo);
                }
                i++;
                all_attributes->getNextNode(tempAttribute);
            }
            all_endowments->append(new_endowment);
        }
    }

}

int openFile(string filepath, bool firstline, bool firsttime) {

    if (firsttime) {
        //26 is the number of columns. I need to find that out here.
        all_attributes = new DoubleyLinkedList<Attribute>[26];
        //400 is the number of rows ,I need to find that out here first. 
        all_endowments = new DoubleyLinkedList<Endowment>[400];
    }
    //input the endowments stuff. 
    ifstream infile;

    infile.open(filepath);
    if (infile)
    {  
        inputEndowmentsData(infile, firstline);
        return 0; //successfully opened the first line of the endowments data.
    }
    else {
        return 1; //error couldn't open filepath.
    }
}

void clearMemory()
{
    delete all_attributes;
    delete all_endowments;
    delete all_students;
}