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

using namespace std;

class CPUProgram
{
public:
    
    CPUProgram(string filename); // constructor cpuProgram.h
    string getLine(int line) const; 
    // function takes an integer as the parameter and returns a string that 
    // contains the program line that corresponds to the integer.
    int getSize() const;
    // for sent  to cpu.h
    int size() const;
    // function returns the number of lines read from the file.
private:
    bool readFile(string filename);
    //function takes a string file name as a parameter, reads the program file 
    //and stores all the program instructions.
    
    vector<string> readFromFile; // for read from file
    
};

#endif /* CPUPROGRAM_H */

