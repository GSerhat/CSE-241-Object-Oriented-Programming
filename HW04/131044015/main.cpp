/* 
 * File:   main.cpp
 * Author: serhat
 *
 * Created on October 23, 2016, 9:12 PM
 */
// This program is a simple cpu program.
// We did OOP techniques.
// There are cpu.h  and cpuProgram.h header files in our program.
// There are cpu.cpp  and cpuProgram.cpp class cpp files in our program.
#include "CPU.h" // called CPU.h
#include "CPUProgram.h" // called CPUProgram.h
#include "Memory.h"
#include "Computer.h"
#include <iostream> // for cin cout
#include <cstdlib> 
#include <string> // for string type

using namespace std;

int main(int argc, char** argv) {
    
    CPU optCPU;
    if(argc != 3){
       cout << "You didn't enter 3 argument" << endl;
       return -1;
    }
    const char* filename = argv[1]; 
    int option = optCPU.atooi(argv[2]);
    
    
    
    Memory myMemory(option);
    if(myMemory.optionControl(option) == -1){
        return -1;
    }
    CPU myCPU(option);
    CPUProgram myCPUProgram(option);
    
    if(!(myCPUProgram.ReadFile(filename)))
        return -1;
    
    Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
    myComputer1.execute();
    
    return 0;
}

