/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.h
 * Author: serhat
 *
 * Created on November 4, 2016, 9:13 PM
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgramDyn.h"
#include "Memory.h"

/***************************Computer Class*************************************/
using Program :: CPUProgramDyn;
class Computer{

public:

    /************************Computer constructors*****************************/
    Computer(CPU& myCPU,CPUProgramDyn& myCPUProgram,Memory& myMemory,int tempOpt);
    Computer(int tempOpt); 

    /************************Setter functions***********************************/
    void setCPU(CPU& tempCPU);
    void setCPUProgram(CPUProgramDyn& tempProgram);
    void setMemory(Memory& tempMemory); 

    /************************Getter functions***********************************/
    CPU& getCPU() const ;
    CPUProgramDyn& getCPUProgram()const ;
    Memory& getMemory() const ;

    /************************Member functions***********************************/
    void execute();

private:

    /**************************New Objects**************************************/
    CPU* newCPU;
    CPUProgramDyn* newProgram;
    Memory* newMemory;
    int option;

};


#endif /* COMPUTER_H */

