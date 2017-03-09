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
#include "CPUProgram.h"
#include "Memory.h"

/***************************Computer Class*************************************/
class Computer{
    
public:
    
    /************************Computer constructors*****************************/
	Computer(CPU& myCPU,CPUProgram& myCPUProgram,Memory& myMemory,int tempOpt);
	Computer(int tempOpt); 

	/************************Setter functions***********************************/
	void setCPU(CPU& tempCPU);
	void setCPUProgram(CPUProgram& tempProgram);
	void setMemory(Memory& tempMemory); 

	/************************Getter functions***********************************/
	CPU& getCPU() const ;
	CPUProgram& getCPUProgram()const ;
	Memory& getMemory() const ;

	/************************Member functions***********************************/
	void execute();

private:
    
    /**************************New Objects**************************************/
    CPU* newCPU;
    CPUProgram* newProgram;
    Memory* newMemory;
    int option;
    
};

#endif /* COMPUTER_H */

