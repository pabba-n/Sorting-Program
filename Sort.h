/*
* Sort.h
*
* Sorting project
* by Nishika Pabba 8/6/2021
*
* Declarations for sorting class.
*/

#ifndef __SORT_H__
#define __SORT_H__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Person.h"
using namespace std;

class Sort {

public:
    Sort(string personsFile);
    void organize(string outputFile);
    void query(ostream &outputFile);
private:
    void readFile(string personsFile);
    vector<Person> list;
    void print(ostream &output);
    void initialMessage(ostream &outputFile);
    bool comparison(string a, string b);
    int partitionFirst(int small, int big);
    void quickSortFirst(int small, int big);
    int partitionLast(int small, int big);
    void quickSortLast(int small, int big);
    int partitionTime(int small, int big);
    void quickSortTime(int small, int big);
    void binarySearchFirst(int start, int end, string name);
    void binarySearchLast(int start, int end, string name);
    int foundIndex;

};

#endif
