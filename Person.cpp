/*
* Person.cpp
*
* Sorting project
* by Nishika Pabba 8/6/2021
*
* Formats printing of Person's info.
*/

#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

/* print
 *    Purpose: To print each person's info.
 * Parameters: ostream reference for output file.
 *    Returns: NONE
 */
void Person::print (ostream &output) {
    output << firstName << " " << lastName << endl;
    output << "Time: ";
    if(min < 0 or min > 59 ){
        totalMin = 0;
        throw runtime_error("INVALID TIME");
    }
    if(hour > -1 and hour < 10){
        output << 0 << hour << ":";
    } else if (hour > 9 and hour < 25){
        output << hour << ":";
    } else {
        totalMin = 0;
        throw runtime_error("INVALID TIME");
    }

    if(min > -1 and min < 10) {
        output << 0 << min << endl;
    } else if (min > 9 and min < 60) {
        output << min << endl;
    } else {
        totalMin = 0;
        throw runtime_error("INVALID TIME");
    }
    output << endl;
}
