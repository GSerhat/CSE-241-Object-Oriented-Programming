/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "CPUProgramDyn.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
//constructor that takes a file name as parameter and calls the functions readFile.
namespace Program
{
    CPUProgramDyn :: CPUProgramDyn(int tempOpt) 
    {
        option = tempOpt;
    }
    CPUProgramDyn :: CPUProgramDyn()
    {}
    CPUProgramDyn :: CPUProgramDyn (const CPUProgramDyn& other):lineLength(other.lineLength),used(other.used)
    {
       readFromFile = new string[lineLength];
       for(int i=0;i<used;++i)
           readFromFile[i]  = other.readFromFile[i];
    }
    int CPUProgramDyn :: getLineLength() const 
    {
        return lineLength;
    }
    int CPUProgramDyn :: getUsed() const 
    {
        return used;
    }
    void CPUProgramDyn :: setLineLength(int _line)
    {
        lineLength = _line;
    }
    void CPUProgramDyn :: setUsed(int _used)
    {
        used = _used;
    }
    bool CPUProgramDyn :: ReadFile(const char* filename) 
    {
        string str;
        fstream inputStream,inputStream_2;
        setLineLength(0);
       
        inputStream.open(filename);
        inputStream_2.open(filename);
        // File can not open
        if(!inputStream.is_open()){
            cout << "Unable to open the specified file"<< endl;
            return false;
        }
        while(getline(inputStream,str)){
            
           ++lineLength;
        }
        
        lineLength*=3;
        
        readFromFile= new string[lineLength];
        
        setUsed(0);
        
        while(getline(inputStream_2,str)){
            
            readFromFile[getUsed()]=str;
            
            ++used;
            
        }
        inputStream.close();
        inputStream_2.close();

        return true;
    }
    string CPUProgramDyn :: getLine(int line) const 
    {
        return readFromFile[line];
    }
    int CPUProgramDyn :: size() const
    {
        return getUsed();
    }
    CPUProgramDyn&  CPUProgramDyn ::  operator=(const CPUProgramDyn& other)
    {
        if(this == &other){
            
            return *this;
        } 
            
        else
        {
            
            setLineLength(other.getLineLength());
            setUsed(other.getUsed()) ;
            
            delete[] readFromFile;
            
            readFromFile = new string[getLineLength()];
            
            for(int i =0;i<getUsed();++i)
                readFromFile[i]= other.readFromFile[i];
            
            return *this;
        }
    }
    string CPUProgramDyn :: operator[](int line) const
    {
        if(line >= size())
        {
            cerr<< "You are taking invalid index"<< endl;
            return "";
        }
        return getLine(line);
    }
    const CPUProgramDyn CPUProgramDyn :: operator+(const string instruction) const
    {
        
        CPUProgramDyn temp = *this;
        
        temp.readFromFile[temp.used] = instruction;
        (temp.used )++;
        
        return temp;
    }
    const CPUProgramDyn& CPUProgramDyn :: operator+=(const string instruction) 
    {
        if(instruction == ""){
            cerr << "You added space line" <<endl;
        }
        
        enlargeArray(instruction);
        
        return *this;

    }
    const CPUProgramDyn  CPUProgramDyn :: operator+(const CPUProgramDyn& myProg2) const
    {
        CPUProgramDyn temp;
        temp.readFromFile = new string[lineLength];
        temp = *this;
        
        
        cout <<temp.used<< endl;
        int i;
        for(i=0;i< myProg2.used;++i){
            temp.readFromFile[temp.used] = myProg2.readFromFile[i];
            
            (temp.used)++;
            
        }
        
        return temp;

    }
    ostream& operator <<(ostream& output , const CPUProgramDyn& myProg)
    {
        
        for(int i=0;i < myProg.used; ++i){
            output << myProg.readFromFile[i]<< endl;
        }
        return output;
    }
    bool CPUProgramDyn :: operator==(const CPUProgramDyn& myProg2)const
    {
        return size() == myProg2.size();
        
    }
    bool CPUProgramDyn :: operator!=(const CPUProgramDyn& myProg2)const
    {
        return !(size() == myProg2.size());
    }
    bool CPUProgramDyn :: operator<(const CPUProgramDyn& myProg2)const
    {
        return size() < myProg2.size();
    }
    bool CPUProgramDyn :: operator>(const CPUProgramDyn& myProg2)const
    {
        return size() > myProg2.size();
    }
    bool CPUProgramDyn :: operator<=(const CPUProgramDyn& myProg2)const
    {
        return !(size() > myProg2.size());
    }
    bool CPUProgramDyn :: operator>=(const CPUProgramDyn& myProg2)const
    {
        return !(size() < myProg2.size());
    }
    CPUProgramDyn CPUProgramDyn ::  operator --()
    {
        --used;
       
        return *this;
    }
    CPUProgramDyn CPUProgramDyn ::  operator --(int)
    {
        CPUProgramDyn temp(*this);
        
        --used;
        
        return temp;
    }
    CPUProgramDyn CPUProgramDyn :: operator ()(const int begin , const int end)
    {
        
        CPUProgramDyn newProg;
        
        int i,j=0;
        
        if(end > size() || begin > size())
        {
            cerr<< "You are taking wrong line" << endl;
            return newProg;
        }
        if(begin > end)
        {
            cerr << "Begin value is the bigger than end value"<< endl;
            return newProg;
        }
        
        int sub = end - begin +1;
        
        newProg.readFromFile = new string[sub];
        newProg.used =0;
        
        for(i= begin,j=0; i <= end ; ++i,++j){
            newProg.readFromFile[j] = readFromFile[i];
            (newProg.used)++;
        }
        return newProg;
    }
    void CPUProgramDyn :: enlargeArray(const string instruction)
    {
        
        if(lineLength <= used)
        {
            string*str= readFromFile;

            lineLength += used - lineLength+1;

            readFromFile = new string[lineLength];

            for(int i=0 ; i < used ; ++i)
                readFromFile[i] =  str[i] ;

            delete [] str;
        }

        ++used;
        readFromFile[used-1] = instruction;
    }
    CPUProgramDyn ::~CPUProgramDyn()
    {   
        delete [] readFromFile;
    }
}
