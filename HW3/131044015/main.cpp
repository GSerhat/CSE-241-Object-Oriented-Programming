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
#include <iostream> // for cin cout
#include <string> // for string type

using namespace std;

int main(int argc, char** argv) {
    
    if(argc != 3){ // control of argument number
        cerr << "Invalid argument!!" << endl;
        return -1;
    }
    if(argv[2][0] != '1' && argv[2][0] != '0'){ // control of option
        cerr << "Invalid argument!!" << endl;
        return -1;
    }
   
    CPUProgram myProg(static_cast<string>(argv[1])); // CpuProgram object
    // We sent the file name
    CPU myCPU; // cpu object
    
    myCPU.setOption(argv[2][0]); // We sent options to cpu.h
    myCPU.setLastLine(myProg.getSize()); // we sent progsize from cpuProgram.h to cpu.h
    
    while(!myCPU.halted()){ // Return condition
    
        string instruction = myProg.getLine(myCPU.getProgramCounter());
       
        myCPU.execute(instruction);
      
    }
    return 0;
}

