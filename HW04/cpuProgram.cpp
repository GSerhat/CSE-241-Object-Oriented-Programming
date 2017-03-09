#include "CPUProgram.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//constructor that takes a file name as parameter and calls the functions readFile.
CPUProgram :: CPUProgram(int tempOpt) 
{
    option = tempOpt;
    
}
bool CPUProgram :: ReadFile(const char* filename) 
{
    string str;
    fstream inputStream;
    
    inputStream.open(filename);
    // File can not open
    if(!inputStream.is_open()){
        cout << "Unable to open the specified file"<< endl;
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
    return readFromFile[line];
}
int CPUProgram :: size() const
{
    return readFromFile.size();
}
