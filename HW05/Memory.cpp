/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "Memory.h"
#include <iostream>
#include <string>

using namespace std;

Memory :: Memory(int tempOpt)
{
    option = tempOpt;
    
    
    for(int i=0 ; i<SIZE_MEMORY ; ++i)
        memoryAddress[i] = 0;
}
int Memory :: getMem(int index) const 
{
    return memoryAddress[index];
}
void Memory :: setMem(int index , int constant)
{
    memoryAddress[index] = constant;
}
int Memory :: optionControl(int option)
{
    if(option != 1 && option != 2 && option != 0 ){
        cout << "Invalid argument option" << endl;
        return -1;
    }
    return 0;
}
void Memory :: printAll() const 
{
    cout << endl;
    for(int i=0; i < SIZE_MEMORY ; ++i ){
        if( i % 5 == 0)
            cout << endl;
        
        cout << "Address " << i << " = " << getMem(i) << " ";
    }
    cout << endl  ;
}

