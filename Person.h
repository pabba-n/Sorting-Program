/*
* Person.h
*
* Sorting project
* by Nishika Pabba 8/6/2021
*
* Declarations and constructors to create a data type called person. 
*/
#ifndef __PERSON_H__
#define __PERSON_H__

#include <iostream>
#include <string>
using namespace std;

struct Person {

    string firstName, lastName;
    int hour, min, totalMin;

    Person(){
        firstName = "";
        lastName = "";
        hour = -1;
        min = -1;
    }

    Person(string first, string last, int hourNum, int minNum){
        firstName = first;
        lastName = last;
        hour = hourNum;
        min = minNum;
        totalMin = (hour * 60) + min;
    }

    void print(ostream &output);
};

#endif
