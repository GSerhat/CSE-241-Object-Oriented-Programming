/* 
 * File:   CPU.h
 * Author: serhat
 *
 * Created on October 23, 2016, 9:12 PM
 */
/* CPU.h headeri */

#ifndef CPU_H
#define CPU_H

#include "Memory.h" 
#include <string>
#define SIZE 5

/******************************Class of CPU************************************/

using namespace std;

class CPU 
{

public:
    
    /************************CPU constructor***********************************/
    CPU();
    CPU(int tempOpt); // Initializies to program counter,all registers and option
    
    /************************Member Functions***********************************/
    void print()const; // function that prints all the registers and the PC
    bool halted()const; 
    // function returns true if the last instruction executed halted the CPU.
    void execute(string instruction,Memory& mymem);
    //function takes a string that contains an instruction line, executes it 
    //and advances the PC accordingly.
    int atooi(char* str); // to convert to int from string
    /************************Getter Functions**********************************/
    int getReg(int index) const; // getter all registers.
    int getProgramCounter() const; // getter program counter
    char getOption() const ; // getter option
    
    /************************Setter Functions**********************************/
    void setReg(int newReg,int index); // setter all registers
    void setProgramCounter(int pC); // setter program counter
    void setOption(int opt); // setter option
     

private:
    
    char* toUpperCase(char* str); // to Upper case sensitivity
    
    int reg[SIZE]; // registers array
    int programCounter;
    bool halt; // flag
    int option; 
    
    /************************Parsing Member Function***************************/
    void parseMoveSubAdd(string instruction,char strOFInstruction[100],int z,Memory& mymem);
    // this function parses move,sub and add instructions.
    void parsePrint(string instruction,char strOFInstruction[100],int z,Memory& mymem);
    // this function parses print instruction.
    void parseJump(string instruction,char strOFInstruction[100],int z,Memory& mymem);
    // this function parses jump instruction.
    
    /************************Instructions Helper Function**********************/
    void moveSubAdd(char*str,char* str1,char* str2,int intFromString,Memory& mymem);
    // to move ,sub and add  operations
    void print(char* str,Memory& mymem); // to print operation.
    int jump(char *str,int intFromString,char strOFInstruction[100],Memory& mymem);
    // jump operation
    
    
};

#endif /* CPU_H */

