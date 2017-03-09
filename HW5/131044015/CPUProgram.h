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
    CPUProgram();
    /************************Member Functions**********************************/
    string getLine(int line) const ; 
    // function takes an integer as the parameter and returns a string that 
    // contains the program line that corresponds to the integer.
    int size() const;
    // function returns the number of lines read from the file.
    bool ReadFile(const char* filename);
    //function takes a string file name as a parameter, reads the program file 
    //and stores all the program instructions.
    /********************Overloading Functions*********************************/
    string operator[]( const int line) const ;
    // Operator[] that takes an integer and works like the getLine function. 
    // It returns the program line as a string.
    const CPUProgram operator+(const string instruction)const;
    //Operator+ that takes a CPUProgram and an instruction line as a string. 
    //It returns a new CPUProgram that has the original CPUProgram with appended 
    //last line from the parameter string.
    const CPUProgram operator+(const CPUProgram& myProg2) const;
    //Operator+ that takes two programs and returns a new program that 
    //appends the second programs to the first one
    
    const CPUProgram& operator+=(string instruction);
    // Operator+= that takes an instruction line as a string and appends 
    // the instruction to the end of the program.
    
    //    All comparison operators ==, !=, <, >=, etc. All comparison operators 
    //    compare the number of lines of the programs.
    bool operator ==(const CPUProgram& myProg2)const;
    bool operator !=(const CPUProgram& myProg2)const;
    bool operator < (const CPUProgram& myProg2)const;
    bool operator > (const CPUProgram& myProg2)const;
    bool operator <=(const CPUProgram& myProg2)const;
    bool operator >=(const CPUProgram& myProg2)const;
    CPUProgram operator --();
    CPUProgram operator --(int);
    //    Post and pre decrement operators - - that 
    //    delete the last line of the program.
    
    // Function call operator() that takes two integers and returns a new 
    // program that contains the instructions between the given integers.
    CPUProgram operator ()(const int begin , const int end);
    //    Operator>> that prints the program
    friend ostream& operator <<(ostream& output , const CPUProgram& myProg);
private:
    
    vector<string> readFromFile; // for read from file
    int option;

};

#endif /* CPUPROGRAM_H */

