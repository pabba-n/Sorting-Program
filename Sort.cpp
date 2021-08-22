/*
* Sort.cpp
*
* Sorting project
* by Nishika Pabba 8/6/2021
*
* Implementation of sorting class. Uses quickSort and binary search algorithms.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include "Sort.h"
#include "Person.h"

/* Sort
 *    Purpose: Constructor
 * Parameters: String of file name with persons list.
 *    Returns: NONE
 */
Sort::Sort(string personsFile){
    readFile(personsFile);
}

/* readFile
 *    Purpose: To open file and collect names and info of each person.
 * Parameters: String of file name with persons list.
 *    Returns: NONE
 */
void Sort::readFile(string personsFile){
    ifstream infile(personsFile);
    if(infile.fail()){
        cerr << "ERROR: " << personsFile << " is an invalid file." << endl;
        exit(EXIT_FAILURE);
    }

    string personInfo = "";
    string first, last, trash;
    int hourTime, minTime;
    getline (infile, personInfo);
    istringstream ss(personInfo);
    ss >> first >> last >> hourTime >> minTime;
    Person newPerson = Person(first, last, hourTime, minTime);
    list.push_back(newPerson);

    while(!infile.eof()){
        getline(infile, personInfo);
        istringstream sstream(personInfo);
        sstream >> first >> last >> hourTime >> minTime;
        Person newPerson = Person(first, last, hourTime, minTime);
        list.push_back(newPerson);
    }
    list.pop_back();
}

/* print
 *    Purpose: To print people's info from list.
 * Parameters: ostream reference for output file.
 *    Returns: NONE
 */
void Sort::print(ostream &output){
    output << endl << "--------------------------" << endl;
    output << "--------------------------" << endl << endl;
    for(int i = 0; i < list.size(); i++){
        try {
            list[i].print(output);
        } catch (runtime_error &message){
            output << message.what() << endl;
            output << endl;
        }
    }
    output << "--------------------------" << endl;
    output << "--------------------------" << endl << endl;
}

/* organize
 *    Purpose: To pass in output file reference depending on command line
 *             arguments given by the user.
 * Parameters: string of output file name
 *    Returns: NONE
 */
void Sort::organize(string outputFile){
    if(outputFile == "") {
        query(cout);
    } else {
        ofstream out(outputFile);
        if (out.fail()){
            cerr << "ERROR: " << outputFile << " is an invalid file." << endl;
            exit(EXIT_FAILURE);
        }
        query(out);
    }
}

/* initialMessage
 *    Purpose: To print message for user input.
 * Parameters: ostream reference for output file.
 *    Returns: NONE
 */
void Sort::initialMessage(ostream &outputFile){

    outputFile << "Which of the following tasks would you like to complete?"
    << endl;
    outputFile << "Type the number from one of the following options:" << endl;
    outputFile << "1. alphabetical by first name" << endl;
    outputFile << "2. alphabetical by last name" << endl;
    outputFile << "3. chronological" << endl;
    outputFile << "4. search for person by first name" << endl;
    outputFile << "5. search for person by last name" << endl;

}

/* query
 *    Purpose: Handles user query inputs from terminal.
 * Parameters: ostream reference for output file.
 *    Returns: NONE
 */
void Sort::query(ostream &outputFile){
    string command;
    //prints initial unsorted info per person
    print(outputFile);

    //prints introductory message
    initialMessage(outputFile);

    //query loop
    while (cin >> command){
        if(command == "1"){
            int num = list.size()-1;
            quickSortFirst(0, num);
            print(outputFile);
        } else if (command == "2"){
            int num = list.size()-1;
            quickSortLast(0, num);
            print(outputFile);
        } else if (command == "3"){
            int num = list.size()-1;
            quickSortTime(0, num);
            print(outputFile);
        } else if (command == "4"){
            string name;
            outputFile << "Enter first name to search for:" << endl;
            cin >> name;
            int num = list.size()-1;
            foundIndex = -1;
            binarySearchFirst(0, num, name);
            if (foundIndex > -1) {
                outputFile << endl << "Found the person at index ["
                << foundIndex << "]!" << endl;
                outputFile << endl
                << "*** list was sorted alphabetically by first name ***"
                << endl << endl;

            } else {
                outputFile << "Person not found :(" << endl;
            }
        } else if (command == "5"){
            string name;
            bool found;
            outputFile << "Enter last name to search for:" << endl;
            cin >> name;
            int num = list.size()-1;
            foundIndex = -1;
            binarySearchLast(0, num, name);
            if (foundIndex >) {
                outputFile << endl << "Found the person at index ["
                << foundIndex << "]!" << endl;
                outputFile << endl
                << "*** list was sorted alphabetically by last name ***"
                << endl << endl;
            } else {
                outputFile << "Person not found :(" << endl;
            }

        } else {
            outputFile << endl << "COMMAND NOT FOUND. Please try again."
            << endl << endl;
        }

        //prints initial message screen so that loop can continue
        initialMessage(outputFile);
    }
}

/* comparison
 *    Purpose: Compares letters between two strings.
 * Parameters: ostream reference for output file.
 *    Returns: NONE
 */
bool Sort::comparison(string a, string b){
    //if letters are equal, iterate to next letter until differing
    //letter is found
    for(int i = 0; i < a.length(); i++){
        //compare differing letters
        if(a[i] < b[i]){
            return true;
        } else if (a[i] > b[i]){
            return false;
        }
    }
    return false;
}

/* partitionFirst
 *    Purpose: Chooses pivot point and partitions list by first name to sort
 *             recursively.
 * Parameters: Integers of small and big indices for the range of partition.
 *    Returns: Next integer for swapping.
 */
int Sort::partitionFirst(int small, int big){
    string pivot = list[big].firstName;
    int j = small-1;
    for (int i = small; i <= big; i++){
        if (comparison(list[i].firstName, pivot)) {
            j++;
            swap(list[j], list[i]);
        }
    }
    swap(list[j+1], list[big]);
    return j+1;
}

/* quickSortFirst
 *    Purpose: Uses quickSort algorithm to partition and sort first names.
 *             Calls partition function to recursively create partitions.
 * Parameters: Integers to signify the indices of the range of partition.
 *    Returns: NONE
 */
void Sort::quickSortFirst(int small, int big){
    if (small < big){
        int index = partitionFirst(small, big);
        quickSortFirst(small, index-1);
        quickSortFirst(index+1, big);
    }
}

/* partitionLast
 *    Purpose: Chooses pivot point and partitions list by last name to sort
 *             recursively.
 * Parameters: Integers of small and big indices for the range of partition.
 *    Returns: Next integer for swapping.
 */
int Sort::partitionLast(int small, int big){
    string pivot = list[big].lastName;
    int j = small-1;
    for (int i = small; i <= big; i++){
        if (comparison(list[i].lastName, pivot)) {
            j++;
            swap(list[j], list[i]);
        }
    }
    swap(list[j+1], list[big]);
    return j+1;
}

/* quickSortLast
 *    Purpose: Uses quickSort algorithm to partition and sort last names.
 *             Calls partition function to recursively create partitions.
 * Parameters: Integers to signify the indices of the range of partition.
 *    Returns: NONE
 */
void Sort::quickSortLast(int small, int big){
    if (small < big){
        int index = partitionLast(small, big);
        quickSortLast(small, index-1);
        quickSortLast(index+1, big);
    }
}

/* partitionTime
 *    Purpose: Chooses pivot point and partitions list by time to sort
 *             recursively.
 * Parameters: Integers of small and big indices for the range of partition.
 *    Returns: Next integer for swapping.
 */
int Sort::partitionTime(int small, int big){


    int pivot = list[big].totalMin;
    int j = small-1;
    for (int i = small; i <= big; i++){
        if (list[i].totalMin <= pivot) {
            j++;
            swap(list[j], list[i]);
        }
    }
    swap(list[j+1], list[big]);
    return j+1;
}

/* quickSortTime
 *    Purpose: Uses quickSort algorithm to partition and sort time.
 *             Calls partition function to recursively create partitions.
 * Parameters: Integers to signify the indices of the range of partition.
 *    Returns: NONE
 */
void Sort::quickSortTime(int small, int big){
    if (small < big){
        int index = partitionTime(small, big);
        quickSortTime(small, index-1);
        quickSortTime(index+1, big);
    }
}

/* binarySearchFirst
 *    Purpose: Sorts first names alphabetically and then uses binary search
 *             algorithm to determine if a first name is in the list.
 * Parameters: Integers to signify the indices of the range of partition.
 *    Returns: Boolean about whether the name was found or not.
 */
void Sort::binarySearchFirst(int start, int end, string name){
    quickSortFirst(start, end);
    int mid = (start + end) / 2;
    while (start <= end) {
        if (list[mid].firstName == name ){
            foundIndex = mid;
            return;
        }

        if(comparison(list[mid].firstName, name)){
            binarySearchFirst(mid + 1, end, name);
        } else {
            binarySearchFirst(start, mid - 1, name);
        }
        return;
    }
}

/* binarySearchLast
 *    Purpose: Sorts last names alphabetically and then uses binary search
 *             algorithm to determine if a last name is in the list.
 * Parameters: Integers to signify the indices of the range of partition.
 *    Returns: Boolean about whether the name was found or not.
 */
void Sort::binarySearchLast(int start, int end, string name){
    quickSortLast(start, end);
    int mid = (start + end)/ 2;
    while(start <= end){
        if (list[mid].lastName == name ){
            foundIndex = mid;
            return;
        }

        if(comparison(list[mid].lastName, name)){
            binarySearchLast(mid + 1, end, name);
        } else {
            binarySearchLast(start, mid - 1, name);
        }
        return;
    }
}
