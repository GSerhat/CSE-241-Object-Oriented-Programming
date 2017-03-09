#include "CPU.h"
#include <iostream>
#include <string>

using namespace std;

CPU :: CPU ()
{
    programCounter = 1;
    halt=false;
    for(int i=0; i<SIZE;++i)
        reg[i] = 0;
}
void CPU :: setReg(int newReg , int index)
{
    reg[index] = newReg;
}
void CPU :: setProgramCounter(int pC)
{
    programCounter = pC ;
}
int CPU :: getReg(int index) const
{
    return reg[index];
}
int CPU :: getProgramCounter() const
{
    return programCounter;
}
void CPU ::setOption(char opt)
{
    option = opt;
}
char CPU ::getOption() const
{
    return option;
}
 void CPU :: print() const
{
    cout << endl;
    for(int i=0; i < SIZE ;++i)
        cout << "R" << i+1 << " = " << getReg(i) << " ";
    cout << endl << "PC = "<< getProgramCounter() << endl;
}
bool CPU :: halted() const
{
    return halt;
}
void CPU ::setLastLine(int line) 
{
    lastLine = line;
}
int CPU ::getLastLine(){
    return lastLine;
}
void CPU :: moveSubAdd(char*str,char* str1,char* str2,int intFromString)
{
    
    char buffer1[2],buffer2[2]; // Which register value
    int z,k; //for turn string to integer

    buffer1[0] = str1[1]; // Is it r1,r2,r3,r4,r5 ?
    buffer1[1] = '\0';
    z = atooi(buffer1); //for turn string to integer
    // is register or constant?
    if(intFromString != -9998) //If value didn't changed
        if(static_cast<string>(str) == "MOV")
            setReg(intFromString,z-1);
        //for Sub
        else if(static_cast<string>(str) == "SUB")
            setReg(getReg(z-1) - intFromString,z-1) ;
        //for Add
        else if(static_cast<string>(str) == "ADD")
            setReg(getReg(z-1) + intFromString,z-1) ;
    
    else
    {   
        buffer2[0] = str2[1]; // Is it r1,r2,r3,r4,r5 ?
        buffer2[1] = '\0';
        k = atooi(buffer2); //for turn string to integer
        if(static_cast<string>(str) == "MOV")
            setReg(getReg(z-1),k-1); // move from register to register
        // for Sub task  
        else if(static_cast<string>(str) == "SUB")
            setReg(getReg(z-1)-getReg(k-1),z-1);
        // for Add task
        else if(static_cast<string>(str) == "ADD")
            setReg(getReg(z-1)+getReg(k-1),z-1);
    } 
}
void CPU :: print(char* str) 
{
    char buffer1[2]; // Which register value
    int z; //for turn string to integer
    
    buffer1[0] = str[1]; // Is it r1,r2,r3,r4,r5 ?
    buffer1[1] = '\0';
    z = atooi(buffer1); //for turn string to integer
   //Print
    if(static_cast<string>(str) != "R1" && 
       static_cast<string>(str) != "R2" && 
       static_cast<string>(str) != "R3" && 
       static_cast<string>(str) != "R4" && 
       static_cast<string>(str) != "R5" )
     
        cout << endl << str << endl;
    else
        cout << getReg(z-1)  ;
}
int CPU ::jump(char *str,int intFromString)
{
    char buffer1[2]; // Which register value
    int z; //for turn string to integer
    int result; // Jump value

    if(static_cast<string>(str) != "R1" && 
       static_cast<string>(str) != "R2" && 
       static_cast<string>(str) != "R3" && 
       static_cast<string>(str) != "R4" && 
       static_cast<string>(str) != "R5" )
    {
        z = atooi(str); //for turn string to integer
        result = z-1;
    }
    else
    {
        buffer1[0] = str[1];
        buffer1[1] = '\0';
        z = atooi(buffer1);
        
        if(getReg(z-1) == 0) 
            // If reg is zero
            result = intFromString-1;
        else
            result = getProgramCounter(); 
    } 
    
    return result;
}
void CPU ::parseMoveSubAdd(string instruction,char strOFInstruction[100],int z)
{
    
    char strOFInstruction2[100],strOFInstruction3[100];
    int count3=0,count4=0;
    int i, intFromString=-9998;
    bool flag = true;
    for(i=z; instruction[i] == ' '; ++i);//ıgnore new space
    //Parameter error
    if( instruction[i] == ',' && instruction[i] == ';' && instruction[i] == '\0'){
        cerr << endl<< "Invalid parameter!!"<<endl;
         
        flag = false;
    }
    if(flag == true)
    {
        for(z=i; instruction[z] != ',' && instruction[z] != ' '; ++z )
        { 
        //read first parameter and assign char array
            strOFInstruction2[count3] = instruction[z];

            ++count3;
        }

        strOFInstruction2[count3] = '\0';
        toUpperCase(strOFInstruction2);
        

        if( static_cast<string>(strOFInstruction2) != "R1" &&
            static_cast<string>(strOFInstruction2) != "R2" && 
            static_cast<string>(strOFInstruction2) != "R3" &&
            static_cast<string>(strOFInstruction2) != "R4" && 
            static_cast<string>(strOFInstruction2) != "R5" )
        {   
            cerr << endl<< "Invalid parameter!!"<<endl;
            
            flag = false;
        }
        if(flag == true){
            if(getOption() == '1')
                cout << " " << strOFInstruction2 << ", " ;
            
            if(instruction[z] == ' ')
            {
                for(z; instruction[z] != ',' && flag == true; ++z )
                {
                    if(instruction[z] != ' ' )
                    {   //Parameter error
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        
                        flag = false;
                    }
                }
            }
            for(z=z+1;instruction[z] == ' '; ++z ); // ıgnore space
            //parameter error
            if(instruction[z] == ';' || instruction[z] == '\0')
            {
                cerr << endl<< "Invalid parameter!!"<<endl;
                
                flag = false;
            }

            if(flag == true)
            {
                for (z; instruction[z] != ';'  && 
                instruction[z] != '\0' && 
                instruction[z] != ' '; ++z )
                {   //read second parameter and assign char array
                    strOFInstruction3[count4] = instruction[z];

                    ++count4;
                }

                strOFInstruction3[count4] = '\0';
                toUpperCase(strOFInstruction3); // case sensitive

                if(static_cast<string>(strOFInstruction3) != "R1" &&
                   static_cast<string>(strOFInstruction3) != "R2" && 
                   static_cast<string>(strOFInstruction3) != "R3" &&
                   static_cast<string>(strOFInstruction3) != "R4" && 
                   static_cast<string>(strOFInstruction3) != "R5" )
                {   
                    if(strOFInstruction3[0] == 'R'){
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        
                        flag = false;
                    }
                    else{   
                        intFromString = atooi(strOFInstruction3);
                        if(getOption() == '1')
                            cout <<intFromString;
                    }
                }
                else{
                    if(getOption() == '1')
                        cout << strOFInstruction3 ;
                } 
                if(flag == true){
                    moveSubAdd(strOFInstruction,strOFInstruction2, strOFInstruction3,intFromString);

                    if(instruction[z] == ' ')
                    {
                        for(z; instruction[z] != ';' && 
                               instruction[z] != '\0' &&
                                flag == true; ++z )
                        {   //Parameter error
                            if(instruction[z] != ' ' )
                            {
                                cerr << endl<< "Invalid parameter!!"<<endl;
                                
                                flag = false;
                            }
                        }
                    }
                }
            }
        }
    }
    if(flag)
    {
        halt=false;
        
    }else
        halt=true;
}
void CPU :: parsePrint(string instruction,char strOFInstruction[100],int z)
{
    char strOFInstruction2[100];
    int count3=0;
    int i, intFromString=-9998;
    bool flag = true;
    
    for(i = z; instruction[i] == ' '; ++i);//Ignore new space

    if(instruction[i] == ';' && instruction[i] =='\0'){
        cerr << endl<< "Invalid parameter!!"<<endl;
        // error
        flag = false;
    }
    if(flag == true){
        for(z=i ; instruction[z] != ';' && 
            instruction[z] != '\0' && 
            instruction[z] != ' ' ; ++z )
        { 
        //read parameter and assign char array
        strOFInstruction2[count3] = instruction[z];

        ++count3;
        }
        strOFInstruction2[count3] = '\0';
        toUpperCase(strOFInstruction2);
        if(getOption() == '1' )
            cout << " " << strOFInstruction2 ;

        if(instruction[z] == ' ')
        {
            for(z; instruction[z] != '\0' && 
                instruction[z] != ';' &&
                flag == true; ++z )
            {
                if(instruction[z] != ' ' && 
                    instruction[z] != ';' )
                {   // Parameter error
                    cerr << endl<< "Invalid parameter1!!"<<endl;
                    
                    flag = false;
                }
            }
        }
    }    
    if(flag == true){
        
        cout << endl; 
        print(strOFInstruction2); // for print
    }
    
    if(flag)
    
        halt=false;
    else
        halt=true;
}
void CPU ::parseJump(string instruction,char strOFInstruction[100],int z)
{
    char strOFInstruction2[100],strOFInstruction3[100];
    int count3=0,count4=0;
    int i, intFromString=-9998;
    bool flag = true;
     
    for(i=z; instruction[i] == ' '; ++i); // Ignore new space
        //Parameter error
        if(instruction[i] == ','){
            cerr << endl<< "Invalid parameter!!"<<endl;
            
            flag = false;
        }
    
        if(flag == true)
        {
            if(instruction[i] == 'R' || instruction[i] == 'r' )
            { // If first parameter is register

                for(z=i ; instruction[z] != ',' && 
                        instruction[z] != ' '; ++z )
                { 
                //read first parameter and assign char array
                    strOFInstruction2[count3] = instruction[z];

                    ++count3;
                }

                strOFInstruction2[count3] = '\0';

                toUpperCase(strOFInstruction2); //Case sensitive
                if(getOption() == '1' )
                    cout << " " << strOFInstruction2 << ", " ;
                
                
                if(instruction[z] == ' ')
                {   //Parameter error
                    for(z; instruction[z] != ',' && flag == true; ++z )
                    {
                        if(instruction[z] != ' ' )
                        {
                            cerr << endl<< "Invalid parameter!!"<<endl;
                            
                            flag = false;
                        }
                    }
                }

                for(z=z+1;instruction[z] == ' '; ++z );//Ignore new line

                if(flag == true)
                {
                    if(instruction[z]==';'&&instruction[z]=='\0'){
                        cerr << endl<< "Invalid parameter!!"<<endl;
                         // print error and quit from program
                        flag = false;
                }

                if(flag == true)
                {
                    for (z; instruction[z] != ';'  && 
                                instruction[z] != '\0' && 
                                instruction[z] != ' '; ++z )
                    {
                    //read second parameter and assign char array
                    strOFInstruction3[count4] = instruction[z];

                    ++count4;

                    }

                    strOFInstruction3[count4] = '\0';

                    intFromString = atooi(strOFInstruction3); 
                    // Turn integer from char array
                    if(getOption() == '1' )
                        cout <<  intFromString ;
                    
                    if(instruction[z] == ' ')
                    {
                        for(z; instruction[z] != ';' && 
                                instruction[z] != '\0' ; ++z )
                        {   // Parameter Error
                            if(instruction[z] != ' ' )
                            {
                                cerr << endl<< "Invalid parameter!!"<<endl;
                                
                                flag=false;
                            }
                        }                    
                    }
                    //If LineAdress entered wrong
                    
                    setProgramCounter(jump(strOFInstruction2,intFromString));
                    // line index
                }
            }
        }
        else
        {
            if(instruction[z]==';'&&instruction[z]=='\0'){
                cerr << endl<< "Invalid parameter!!"<<endl;
                i=instruction.length()-1;
                flag = false;
            }
            if(flag == true)
            {
                for(z ;instruction[z] != ';' && 
                        instruction[z] != '\0' ; ++z )
                { 
                //read  parameter and assign char array
                    if(instruction[z] != ' ')
                    {
                        strOFInstruction2[count3] = instruction[z];

                        ++count3;
                    }
                }

                strOFInstruction2[count3] = '\0';
                
                if(getOption() == '1' )
                    cout << " " << strOFInstruction2 << " " ;
                

                intFromString = atooi(strOFInstruction2);
                //If LineAdress entered wrong
                
                setProgramCounter(jump(strOFInstruction2,intFromString));

                cout << "  ";
                }
            }
        }
    if(flag)
        halt=false;
        
    else
        halt=true;
}
void CPU :: execute(string instruction)
{
    char strOFInstruction[100];
    int  count2=0;
    int i,z; //For point and turn from string to integer
    bool flag =true;
    
    if(getOption() == '1')
        cout << endl;
    
    for(i = 0 ; instruction[i] == ' '; ++i);
    
    for(z=i ; instruction[z] != ' ' ; ++z)
    {
        strOFInstruction[count2] = instruction[z]; 
        count2 ++;
    }
    
    strOFInstruction[count2] = '\0';
    toUpperCase(strOFInstruction);
    if(instruction[z] == ' '|| instruction[z] == '\0' || instruction[z] == ',' )
    {
        if(getOption() == '1')
            cout << strOFInstruction ;

        if(static_cast<string>(strOFInstruction) == "MOV" )

            parseMoveSubAdd(instruction,strOFInstruction,z);

        else if(static_cast<string>(strOFInstruction) == "SUB" )

            parseMoveSubAdd(instruction,strOFInstruction,z);

        else if(static_cast<string>(strOFInstruction) == "ADD" )

            parseMoveSubAdd(instruction,strOFInstruction,z);

        else if(static_cast<string>(strOFInstruction) == "PRN" )

            parsePrint(instruction,strOFInstruction,z);
        
        else if(static_cast<string>(strOFInstruction) == "JMP" )

            parseJump(instruction,strOFInstruction,z);

        else if(static_cast<string>(strOFInstruction) == "HLT" )
        {   
            for(z ; instruction[z] != ';' && 
                    instruction[z] != ' ' && 
                    instruction[z] != '\0' && flag != false; ++z )
            {   // Error: If there is parameter
                if (instruction[z] != ' ' && instruction[z] != ';' && 
                    instruction[z] != '\0')
                {
                    cerr << endl <<  "Invalid instruction !!" << endl;

                    flag = false;
                }
            }
            cout << endl;
            if(flag = true){
                if(getOption()== '0')
                    print();
                halt=true;
            }
            
        }
        else{ 
            cerr << endl << "Invalid instruction!!" << endl;

            flag = false;
        }

        if(flag == false)
        {
            halt=true;
        }
        if(getOption()== '1')
            print();
        setProgramCounter(getProgramCounter() +1);
    }
}
char* CPU :: toUpperCase(char* str)
{   //Read until end of line
    for(int i =0;str[i] != '\0'; ++i){
        
        if(str[i] >= 'a' && str[i] <= 'z' )
            str[i] = str[i] - 'a' + 'A';
    }

    return str;
}
int CPU :: atooi(char* str)
{
    int total = 0;
    int neg=1; 
    //Read until end of line
    for (int i = 0; str[i] != '\0'; ++i){
        
        if(str[i] == '-')
            //If it have to -
            neg = -1;
        else
            total = total*10 + str[i] - '0';// Turn to integer
    }
   
    return neg*total;
}
    
