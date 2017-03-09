/* 
 * File:   CPUProgramDyn.h
 * Author: serhat
 *
 * Created on November 26, 2016, 10:45 PM
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H

#include <iostream>
#include <string>


/***************************CPUProgram Class***********************************/
using namespace std ;

namespace Program
{
    class CPUProgramDyn
    {

    public:

    /************************CPUProgram constructor****************************/
        CPUProgramDyn(int tempOpt); // constructor cpuProgram.h
        CPUProgramDyn();
        CPUProgramDyn (const CPUProgramDyn& other);
    /************************Member Functions**********************************/
        string getLine(int line) const ; 
        // function takes an integer as the parameter and returns a string that 
        // contains the program line that corresponds to the integer.
        int size() const ;
        // function returns the number of lines read from the file.
        bool ReadFile(const char* filename);
        //function takes a string file name as a parameter, reads the program file 
        //and stores all the program instructions.
    /********************Overloading Functions*********************************/
        string operator[]( int line)const ;
        // Operator[] that takes an integer and works like the getLine function. 
        // It returns the program line as a string.
        const CPUProgramDyn operator+(const string instruction)const ;
        //Operator+ that takes a CPUProgram and an instruction line as a string. 
        //It returns a new CPUProgram that has the original CPUProgram with appended 
        //last line from the parameter string.
        const CPUProgramDyn operator+(const CPUProgramDyn& myProg2) const ;
        //Operator+ that takes two programs and returns a new program that 
        //appends the second programs to the first one

        const CPUProgramDyn& operator+=(string instruction) ;
        // Operator+= that takes an instruction line as a string and appends 
        // the instruction to the end of the program.
        CPUProgramDyn&  operator=(const CPUProgramDyn& other);
         
        //    All comparison operators ==, !=, <, >=, etc. All comparison operators 
        //    compare the number of lines of the programs.
        bool operator ==(const CPUProgramDyn& myProg2)const;
        bool operator !=(const CPUProgramDyn& myProg2)const;
        bool operator < (const CPUProgramDyn& myProg2)const;
        bool operator > (const CPUProgramDyn& myProg2)const;
        bool operator <=(const CPUProgramDyn& myProg2)const;
        bool operator >=(const CPUProgramDyn& myProg2)const;
        CPUProgramDyn operator --();
        CPUProgramDyn operator --(int);
        //    Post and pre decrement operators - - that 
        //    delete the last line of the program.

        // Function call operator() that takes two integers and returns a new 
        // program that contains the instructions between the given integers.
        CPUProgramDyn operator ()(const int begin , const int end);
        //    Operator>> that prints the program
        friend ostream& operator <<(ostream& output , const CPUProgramDyn& myProg);
        int getLineLength() const ;
        int getUsed() const ;
        void setLineLength(int _line);
        void setUsed(int _used);
        void enlargeArray(const string instruction);
        ~CPUProgramDyn(); //Destructor
    private:
        string* readFromFile ;
        int lineLength;
        int used;
        int option;
        
    };
} // Program

#endif /* CPUPROGRAMDYN_H */

