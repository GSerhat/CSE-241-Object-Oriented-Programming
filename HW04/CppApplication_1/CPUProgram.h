/* 
 * File:   CPUProgram.h
 * Author: serhat
 *
 * Created on October 23, 2016, 10:21 PM
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <vector> // for read from file to vector array 

/***************************CPUProgram Class***********************************/
using namespace std;

class CPUProgram
{

public:
    
    /************************CPUProgram constructor****************************/
    CPUProgram(int tempOpt); // constructor cpuProgram.h
    
    /************************Member Functions**********************************/
    string getLine(int line) const; 
    // function takes an integer as the parameter and returns a string that 
    // contains the program line that corresponds to the integer.
    int size() const;
    // function returns the number of lines read from the file.
    bool ReadFile(const char* filename);
    //function takes a string file name as a parameter, reads the program file 
    //and stores all the program instructions.

private:
    
    vector<string> readFromFile; // for read from file
    int option;

};

#endif /* CPUPROGRAM_H */

