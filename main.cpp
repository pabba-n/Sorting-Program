/*
* main.cpp
*
* Sorting project
* by Nishika Pabba 8/6/2021
*
* Takes arguments from command line and passes them into the program.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Sort.h"
#include "Person.h"

int main(int argc, char *argv[]) {
    if (argc < 2 or argc >3) {
        cerr << "ERROR: Only 2 command line arguments are allowed =>" <<
         " text file name and output file name " << endl;
        exit(EXIT_FAILURE);
    } else if (argc == 2){
        Sort Sorting(argv[1]);
        Sorting.organize("");
    } else if (argc == 3 ){
        Sort Sorting(argv[1]);
        Sorting.organize(argv[2]);
    }
    return 0;
}
