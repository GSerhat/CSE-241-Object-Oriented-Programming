/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: serhat
 *
 * Created on November 4, 2016, 1:32 AM
 */

#ifndef MEMORY_H
#define MEMORY_H

#define SIZE_MEMORY 50

/****************************Memory Class**************************************/
class Memory {

public:
    /************************Memory constructor********************************/
    Memory(int tempOpt);
    /*************************Member Function *********************************/
    int getMem(int index) const;// Getter Memory object
    void setMem(int index , int constant); // seeter memory object
    void printAll() const ;
    int optionControl(int option);
private:
    
    int option; 
    unsigned int memoryAddress[SIZE_MEMORY]; // Memory Addres Array
};

#endif /* MEMORY_H */