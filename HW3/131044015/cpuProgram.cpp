#include "CPUProgram.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//constructor that takes a file name as parameter and calls the functions readFile.
CPUProgram :: CPUProgram(string filename) 
{
    readFile(filename);
}
bool CPUProgram :: readFile(string filename) 
{
    string str;
    fstream inputStream;
    inputStream.open(filename.c_str());
    
    if(!inputStream.is_open()){
        cout << "Unable to open the specified file";
        return false;
    }
    while(getline(inputStream,str)){
        
        readFromFile.push_back(str);
    }
    inputStream.close();
    
    return true;
}
string CPUProgram :: getLine(int line) const
{
    return readFromFile[line-1];
}
int CPUProgram :: size() const
{
    return readFromFile.size();
}
int CPUProgram :: getSize() const
{
    return size();
}



