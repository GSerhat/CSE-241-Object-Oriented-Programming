/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Computer.h"

Computer :: Computer(CPU& myCPU,CPUProgram& myCPUProgram,Memory& myMemory,int tempOpt)
:newCPU(&myCPU) 
,newProgram(&myCPUProgram)
,newMemory(&myMemory)
{
    option = tempOpt;
    
}
Computer :: Computer(int tempOpt)
{
    newCPU = 0;
    newProgram = 0;
    newMemory = 0;        
            
    option = tempOpt;
}
void Computer :: setCPU(CPU& tempCPU )
{
    newCPU = &tempCPU;
}
void Computer :: setCPUProgram(CPUProgram& tempProgram)
{
    newProgram = &tempProgram;
}
void Computer :: setMemory(Memory& tempMemory)
{
    newMemory = &tempMemory;
}
CPU& Computer :: getCPU() const 
{
    return *newCPU;
}
CPUProgram& Computer ::  getCPUProgram() const 
{
    return *newProgram;
}
Memory& Computer ::  getMemory() const
{
    return *newMemory;
}
void Computer :: execute()
{
    
    while(!getCPU().halted()){ // Return condition

        string instruction = getCPUProgram().getLine(getCPU().getProgramCounter()-1);
        
        getCPU().execute(instruction,getMemory());
        
    }
    cout << endl; 
    
}

