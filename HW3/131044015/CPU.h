/* 
 * File:   CPU.h
 * Author: serhat
 *
 * Created on October 23, 2016, 9:12 PM
 */
/* CPU.h headeri */

#ifndef CPU_H
#define CPU_H

#include <string>
#define SIZE 5

using namespace std;
class CPU 
{
public:
    CPU(); // Initializies to program counter and all registers
    void print()const; // function that prints all the registers and the PC
    bool halted()const; 
    // function returns true if the last instruction executed halted the CPU.
    void execute(string instruction);
    //function takes a string that contains an instruction line, executes it 
    //and advances the PC accordingly.
    int getReg(int index) const; // getter all registers.
    int getProgramCounter() const; // getter program counter
    char getOption() const ; // getter option
    int getLastLine(); // getter line number in file
    void setReg(int newReg,int index); // setter all registers
    void setProgramCounter(int pC); // setter program counter
    void setLastLine(int line); // setter line number in file
    void setOption(char opt); // setter option
     

private:
    char* toUpperCase(char* str); // to Upper case sensitivity
    int atooi(char* str); // to convert to int from string
    int reg[SIZE]; // registers array
    int programCounter;
    int lastLine; // line number in file
    bool halt; // flag
    void parseMoveSubAdd(string instruction,char strOFInstruction[100],int z);
    // this function parses move,sub and add instructions.
    void parsePrint(string instruction,char strOFInstruction[100],int z);
    // this function parses print instruction.
    void parseJump(string instruction,char strOFInstruction[100],int z);
    // this function parses jump instruction.
    void moveSubAdd(char*str,char* str1,char* str2,int intFromString);
    // to move ,sub and add  operations
    void print(char* str); // to print operation.
    int jump(char *str,int intFromString);
    // jump operation
    char option;
    
};

#endif /* CPU_H */

