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
CPUProgram :: CPUProgram(){}
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
string CPUProgram :: operator[](int line) const
{
    if(line > size()-1)
    {
        cerr<< "You are taking invalid index"<< endl;
        return "";
    }
    return getLine(line);
}
const CPUProgram CPUProgram :: operator+(const string instruction) const
{
   
    CPUProgram temp = *this;
    temp.readFromFile.push_back(instruction);
    
    return temp;
}
const CPUProgram& CPUProgram :: operator+=(const string instruction) 
{
    if(instruction == ""){
        cerr << "You added space line" <<endl;
    }
    readFromFile.push_back(instruction);
    return *this;
    
}
const CPUProgram  CPUProgram :: operator+(const CPUProgram& myProg2)const
{
    CPUProgram temp = *this;
    for(int i=0;i< myProg2.readFromFile.size();++i){
       
         temp.readFromFile.push_back(myProg2.readFromFile[i]);
    }
   
    
    return temp;
    
}
ostream& operator <<(ostream& output , const CPUProgram& myProg)
{
    for(int i=0;i < myProg.readFromFile.size(); ++i){
        output << myProg.readFromFile[i]<< endl;
    }
    return output;
}
bool CPUProgram :: operator==(const CPUProgram& myProg2)const
{
    return size() == myProg2.size();
}
bool CPUProgram :: operator!=(const CPUProgram& myProg2)const
{
    return !(size() == myProg2.size());
}
bool CPUProgram :: operator<(const CPUProgram& myProg2)const
{
    return size() < myProg2.size();
}
bool CPUProgram :: operator>(const CPUProgram& myProg2)const
{
    return size() > myProg2.size();
}
bool CPUProgram :: operator<=(const CPUProgram& myProg2)const
{
    return !(size() > myProg2.size());
}
bool CPUProgram :: operator>=(const CPUProgram& myProg2)const
{
    return !(size() < myProg2.size());
}
CPUProgram CPUProgram ::  operator --()
{
    readFromFile.pop_back();
    
    return *this;
}
CPUProgram CPUProgram ::  operator --(int)
{
    CPUProgram temp(*this);
    readFromFile.pop_back();
    
    return temp;
}
CPUProgram CPUProgram :: operator ()(const int begin , const int end)
{
    CPUProgram newProg;
    int i,j=0;
    if(end > readFromFile.size() || begin > readFromFile.size())
    {
        cerr<< "You are taking wrong line" << endl;
        return newProg;
    }
    
    if(begin > end)
    {
        cerr << "Begin value is the bigger than end value"<< endl;
        return newProg;
    }
    for(i= begin,j=0; i <= end ; ++i,++j){
        readFromFile[j] = readFromFile[i];
    }
    
    readFromFile.resize(j);
    
    newProg = *this;
    
    return newProg;
}
















