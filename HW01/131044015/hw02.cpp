/* 
 * File:   hw02.cpp
 * Author: Serhat Güzel
 *
 * Created on September 26, 2016, 10:57 PM
 * 
 *
 * This program is a simplu CPU program and as example , we did sort.
 *
 */


#include <iostream>
#include <fstream> /*File Operations*/
#include <string>

using namespace std;

void print(unsigned int *address,int* reg ,char* str); /*Print the given constant-register or memory */
int* moveSubAdd(unsigned int *address,int* reg,char*str,char* str1,char* str2,int inFromString);
//Move from register to register , from constant to register , from memory to register ,
//from register to memory or from memory to constant
/*Subtraction from register until register, constant or from register to memory */
/*Addition from register until register, constant or from register to memory */
int jump(char strOFInstruction[100],int* reg ,char* str ,int inFromString,int i);
/*Jump other line */
int atooi(char* str);
/*Turn from character array to integer*/
char* toUpperCase(char* str);
/*Case sensitive*/
void readInstructions(unsigned int *address,string* readFromFile,int row,
                      int reg[],int size,char** argv);
/*Basic operations*/
void option(int* reg);/*Print*/
//this function does parse task for print operation
bool parsePrint(unsigned int *address,string* readFromFile,int i,int row,
                char strOFInstruction[100],char strOFInstruction2[100],char ** argv, int* reg,int t);
//this function does parse task for Move, Sub , Add operation
bool parseMoveSubAdd(unsigned int *address,string* readFromFile,int i,int row,
                     char strOFInstruction[100],char strOFInstruction2[100],
                     char strOFInstruction3[100],char ** argv,int* reg,
                     int intFromString,int t,int j);
//this function does parse task for Jump operation
int parseJump(string* readFromFile,int i,int row,char strOFInstruction[100],
              char strOFInstruction2[100],char strOFInstruction3[100],
              char ** argv,int* reg,int intFromString,int t);

int main(int argc, char** argv) 
{
    int NUM_OF_REGISTER=5,m; /*Register array size and point*/
    string readFromFile[200]; /*General read from file*/
    int reg[NUM_OF_REGISTER],row=0;  /*Register array and  file line*/
    unsigned int address[50]; // memory ARRAY
    fstream inputStream(argv[1]);
    /*Initialize register array*/
    for(int j= 0 ; j<NUM_OF_REGISTER ; ++j)
        reg[j]=0;
    /*Initialize memory array*/
    for(int j= 0 ; j<50 ; ++j)
        address[j]=0;
    /*File operations-Open file*/
    inputStream.is_open();
    // Read from file 
    while(getline(inputStream,readFromFile[row]))
    {
        ++ row;
        
        if(inputStream.eof())
            break ; 
    }
    /*If argument entered lower or bigger than 3*/
    if(argc != 3){
            cerr << "Invalid argument!!" << endl;
            
            return 0;
    }
    inputStream.close();
    // Basic operations
    readInstructions(address,readFromFile,row,reg,NUM_OF_REGISTER,argv);
    
    return 0;
}
/*Basic operations*/
void readInstructions(unsigned int *address,string* readFromFile,int row,
                        int reg[],int size, char** argv)
{

    char strOFInstruction[100],strOFInstruction2[100],strOFInstruction3[100];
    /*Division-Parse Instruction*/
    int  count2,count3,count4; /*Flag-Counter*/
    int z,intFromString; //For point and turn from string to integer
    bool flag =true;
    // Loop row
    for(int i=0; i < row ; ++ i)
    {
        count2 = 0;
        intFromString = -9998; // Flag value
        if(argv[2][0] == '1' || argv[2][0] == '2') // If option is 1
            cout << endl;
        int l,k,m,j; /*Points*/
        
        // Loop column
        // For ignore new space
        for(l=0;readFromFile[i][l] == ' ';++l);
            
        //Look to the end of each line
        for(int t=l; t <=readFromFile[i].size(); ++t)
        {   
            if(readFromFile[i][t] != ' ')
            {   // Read Instruction and assign char array 
                // assign until see to new space
                strOFInstruction[count2] = readFromFile[i][t];
                
                count2++;

            }
            if(readFromFile[i][t] == ' '|| readFromFile[i][t] == '\0' || readFromFile[i][t] == ',' )
            {
                strOFInstruction[count2] = '\0';
                
                toUpperCase(strOFInstruction); // case sensitive
                if(argv[2][0] == '1' || argv[2][0] == '2')
                    cout << strOFInstruction;
                
                //If Instruction is MOV
                if(static_cast<string>(strOFInstruction) == "MOV" )
                // If flag is false , give error message and quit
                    flag=parseMoveSubAdd(address,readFromFile,i,row,strOFInstruction,
                                    strOFInstruction2,strOFInstruction3,argv,reg,
                                    intFromString,t,j);
                    
                //If Instruction is SUB
                else if(static_cast<string>(strOFInstruction) == "SUB") 
                // If flag is false , give error message and quit
                    flag=parseMoveSubAdd(address,readFromFile,i,row,strOFInstruction,
                                    strOFInstruction2,strOFInstruction3,argv,reg,
                                    intFromString,t,j);

                
                //If Instruction is ADD  
                else if(static_cast<string>(strOFInstruction) =="ADD") 
                // If flag is false , give error message and quit
                    flag=parseMoveSubAdd(address,readFromFile,i,row,strOFInstruction,
                                    strOFInstruction2,strOFInstruction3,argv,reg,
                                    intFromString,t,j);
                
                //If Instruction is PRN
                else if(static_cast<string>(strOFInstruction) =="PRN")
                // If flag is false , give error message and quit
                    flag=parsePrint(address,readFromFile,i,row,strOFInstruction
                               ,strOFInstruction2,argv,reg,t);
                    
                
                //If Instruction is JMP
                else if(static_cast<string>(strOFInstruction) =="JMP")
                    i=parseJump(readFromFile,i,row,strOFInstruction,
                                strOFInstruction2,strOFInstruction3,argv,reg,
                                intFromString,t);
                //If Instruction is JPN
                else if(static_cast<string>(strOFInstruction) =="JPN")
                     i=parseJump(readFromFile,i,row,strOFInstruction,
                                 strOFInstruction2,strOFInstruction3,argv,reg,
                                 intFromString,t);  
                
                /*If Instruction is HALT */
                else if(static_cast<string>(strOFInstruction) =="HLT")
                {
                    /*read newline or ; or \0*/
                    for(z=t ; readFromFile[i][z] != ';' && 
                              readFromFile[i][z] != '\0' ; ++z )
                    {   // Error: If there is parameter
                        if (readFromFile[i][z] != ' ')
                        {
                            cerr << endl <<  "Invalid instruction!!" << endl;
                            i=row - 1;
                            flag = false;
                        }
                    }
                    cout << "      ";
                    i = row ; //EXIT
                }
                else
                {   //Error: Quit
                    cerr << endl << "Invalid instruction!!" << endl;
                    i=row-1;
                    flag = false;
                }

                t =readFromFile[i].size();
            }
        }
        if(flag == true){
            /*If Option is 1*/
            if( argv[2][0] == '1'){
                if(static_cast<string>(strOFInstruction) != "PRN")
                    option(reg);
            }
            // If option is 2
            else if(argv[2][0] == '2'){
                if(static_cast<string>(strOFInstruction) != "PRN")// except
                    option(reg); 
                cout << endl;
                for(int m=0;m < 50;++m){ // Print the address memory
                    cout << " Address " << m << ": " << address[m] ;
                    if((m+1) % 5 == 0)
                        cout << endl;
                }
            }
            else if(argv[2][0] != '0'){
                cout<<"Invalid argument" <<endl;
                i= row; // error
                break;
            }
        }
        else{
            i = row -1; // If flag is false , quit from program
        }
    }
    /*If Option is 0*/
    if(argv[2][0] == '0')
        cout << endl<< "R1 = " << reg[0] << " R2 = " << reg[1] << " R3 = " 
             << reg[2] << " R4 = " << reg[3] << " R5 = " << reg[4] ;
            
    cout << endl;
}
//Move from register to register , from constant to register , from memory to register ,
//from register to memory or from memory to constant
/*Subtraction from register until register, constant or from register to memory */
/*Addition from register until register, constant or from register to memory */
int* moveSubAdd(unsigned int *address,int* reg,char*str,char* str1 ,char* str2 ,int inFromString)
{   
    char buffer1[3],buffer2[3]; // Which register value
    int z,k; //for turn string to integer
    int m,t; // point
    if(str1[0] == '#'){ //  IF first piece is memory
        for(m=0,t=1;str1[m] != '\0';++m,++t)
            buffer1[m] = str1[t];

        buffer1[m] = '\0';
        z = atooi(buffer1); // memory index
    }
    else{
        buffer1[0] = str1[1]; // Is it r1,r2,r3,r4,r5 ?
        buffer1[1] = '\0';
        z = atooi(buffer1); // register index

    }
    // If first inFromString changed 
    if(inFromString != -9998){
        //Mov
        if(static_cast<string>(str) == "MOV"){
            if(str1[0] == '#'){
                address[z] = inFromString;
            }
            else
                reg[z-1] = inFromString;
        }//Sub
        else if(static_cast<string>(str) == "SUB")
            reg[z-1] = reg[z-1] - inFromString;
        //for Add
        else if(static_cast<string>(str) == "ADD")
            reg[z-1] = reg[z-1] + inFromString;
    } 
    //If value didn't changed
    else
    {   
        if(str2[0] == '#'){ // If second piece is memory 
            for(m=0,t=1;str2[m] != '\0';++m,++t)
                buffer2[m] = str2[t];

            buffer2[m] = '\0';
            k = atooi(buffer2); //for turn string to integer. //Memory index

        }
        else{
            buffer2[0] = str2[1]; // Is it r1,r2,r3,r4,r5 ?
            buffer2[1] = '\0';
            k = atooi(buffer2); //for turn string to integer . register index
        }
        
        // for Move task
        if(static_cast<string>(str) == "MOV"){
            
            if(str1[0] == 'R'){
                
                if(str2[0] == 'R')
                    reg[k-1] = reg[z-1]; // move from register to register
                else
                    address[k] = reg[z-1];
            }
            else
                reg[k-1] = address[z];
            
        } // for Sub task  
        else if(static_cast<string>(str) == "SUB"){

            if(str2[0] == 'R')
                reg[z-1] = reg[z-1] - reg[k-1];
            else
                reg[z-1] = reg[z-1] - address[k];
        }
        // for Add task
        else if(static_cast<string>(str) == "ADD"){

            if(str2[0] == 'R')
                reg[z-1] = reg[z-1] + reg[k-1];
            else
                reg[z-1] = reg[z-1] + address[k];
        }
    }
    
    return reg;
}
/*Print the given value*/
void print(unsigned int *address,int* reg ,char* str)
{
    char buffer1[3]; // Which register value
    int z; //for turn string to integer
    if(str[0] == '#'){ //IF first piece is memory
        for(int m=0,k=1;str[m] != '\0';++m,++k)
            buffer1[m] = str[k]; // Is it r1,r2,r3,r4,r5 ?
        buffer1[2] = '\0';
        z = atooi(buffer1); // memory index
    }
    else{
        buffer1[0] = str[1]; // Is it r1,r2,r3,r4,r5 ?
        buffer1[1] = '\0';
        z = atooi(buffer1); // Register index
    }
    //Print
    if(static_cast<string>(str) != "R1" && static_cast<string>(str) != "R2" && 
       static_cast<string>(str) != "R3" && static_cast<string>(str) != "R4" && 
       static_cast<string>(str) != "R5")
        if(str[0] == '#')
            cout << address[z] << endl ; 
        
        else
            cout << endl << str << endl;
    else
        cout << reg[z-1] ;
}
/*Jump other line */
int jump(char strOFInstruction[100],int* reg ,char* str ,int inFromString, int i)
{
    char buffer1[3]; // Which register value
    int z; //for turn string to integer
    int result; // Jump value

    if(static_cast<string>(str) != "R1" && 
       static_cast<string>(str) != "R2" && 
       static_cast<string>(str) != "R3" && 
       static_cast<string>(str) != "R4" && 
       static_cast<string>(str) != "R5" )
    {
        z = atooi(str); //for turn string to integer
        result = z-1; // for Jump index
    }
    else
    {
        buffer1[0] = str[1]; // line
        buffer1[1] = '\0';
        z = atooi(buffer1);
        // If instruction is jmp
        if(static_cast<string>(strOFInstruction) == "JMP"){
            if(reg[z-1] == 0) // If reg is zero
                result = inFromString-2;
            else
                result = i; 
        }// If instruction is jpn
        else if(static_cast<string>(strOFInstruction) == "JPN"){
            if(reg[z-1] <= 0) // If reg is zero
                result = inFromString-2;
            else
                result = i;
        }
        
    }
    
    return result; // it jumpes that you wanted to line 
}
/*Turn from character array to integer*/
int atooi(char* str)
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
/*Case sensitive*/
char* toUpperCase(char* str)
{   //Read until end of line
    for(int i =0;str[i] != '\0'; ++i){
        
        if(str[i] >= 'a' && str[i] <= 'z' )
            str[i] = str[i] - 'a' + 'A';
    }

    return str;
}
bool parseMoveSubAdd(unsigned int *address,string* readFromFile,int i,
    int row,char strOFInstruction[100],
    char strOFInstruction2[100],char strOFInstruction3[100],
    char ** argv,int* reg,int intFromString,int t,int j){

    int count3=0,count4=0,k,z;
    bool flag =true; // If it is false , print error and quit from program
    
    for(k=t; readFromFile[i][k] == ' '; ++k);//ıgnore new space
    //Parameter error
    if( readFromFile[i][k] == ','){
        cerr << endl<< "Invalid parameter!!"<<endl;
        i=row-1; 
        flag = false;
    }
    if(flag == true){
        for(z=k; readFromFile[i][z] != ',' && readFromFile[i][z] != ' '; ++z )
        { 
        //read first parameter and assign char array
            strOFInstruction2[count3] = readFromFile[i][z];

            ++count3;
        }
        
        strOFInstruction2[count3] = '\0';
        toUpperCase(strOFInstruction2); // case sensitive
      
        if(static_cast<string>(strOFInstruction2) != "R1" &&
           static_cast<string>(strOFInstruction2) != "R2" && 
           static_cast<string>(strOFInstruction2) != "R3" &&
           static_cast<string>(strOFInstruction2) != "R4" && 
           static_cast<string>(strOFInstruction2) != "R5" )
        {   
            if(strOFInstruction2[0] != '#'){
                cerr << endl<< "Invalid parameter!!"<<endl;
                i=row-1;
                flag = false;
            }
                
        }
        
        if(flag == true){
            
            if(argv[2][0] == '1' || argv[2][0] == '2')
                cout << " " << strOFInstruction2 << ", " ;
        
            if(readFromFile[i][z] == ' ')
            {
                for(z; readFromFile[i][z] != ',' && flag == true; ++z )
                {
                    if(readFromFile[i][z] != ' ' )
                    {   //Parameter error
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        i=row-1;
                        flag = false;
                    }
                }
            }
            for(z=z+1;readFromFile[i][z] == ' '; ++z ); // ıgnore space
            //parameter error
            if(readFromFile[i][z] == ';' || readFromFile[i][z] == '\0'){
                cerr << endl<< "Invalid parameter!!"<<endl;
                i=row-1;
                flag = false;
            }
            
            if(flag == true)
            {
                for (j = z; readFromFile[i][j] != ';'  && 
                readFromFile[i][j] != '\0' && 
                readFromFile[i][j] != ' '; ++j )
                {   //read second parameter and assign char array
                    strOFInstruction3[count4] = readFromFile[i][j];

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
                    if(strOFInstruction3[0] != '#'){
                        intFromString = atooi(strOFInstruction3);
                        if(argv[2][0] == '1' || argv[2][0] == '2')
                            cout << intFromString ;
                    }
                    else
                        cout << strOFInstruction3 ;

                }
                else{
                    if(argv[2][0] == '1' || argv[2][0] == '2')
                        cout << strOFInstruction3 ;
                } 
                                    
                moveSubAdd(address,reg,strOFInstruction,strOFInstruction2,
                           strOFInstruction3,intFromString);
                               
                if(readFromFile[i][j] == ' ')
                {
                    for(j; readFromFile[i][j] != ';' && 
                           readFromFile[i][j] != '\0' &&
                            flag == true; ++j )
                    {   //Parameter error
                        if(readFromFile[i][j] != ' ' )
                        {
                            cerr << endl<< "Invalid parameter!!"<<endl;
                            i=row-1;
                            flag = false;
                        }
                    }
                }
            } 
        }
    } 
    return flag; //If flag is false , There is error and print error 
                //and quit from program
}
bool parsePrint(unsigned int *address,string* readFromFile,int i,
    int row,char strOFInstruction[100],char strOFInstruction2[100],char ** argv,int* reg,int t){

    bool flag =true; //If it is false , quit from program  
    int count3=0 , k , z; // point and counter
    for(k=t; readFromFile[i][k] == ' '; ++k);//Ignore new space

    if(readFromFile[i][k] == ';' && readFromFile[i][k] =='\0'){
        cerr << endl<< "Invalid parameter!!"<<endl;
        i=row-1; // error
        flag = false;
    }
    if(flag == true){
        for(z=k ; readFromFile[i][z] != ';' && 
            readFromFile[i][z] != '\0' && 
            readFromFile[i][z] != ' ' ; ++z )
        { 
        //read parameter and assign char array
        strOFInstruction2[count3] = readFromFile[i][z];

        ++count3;
        }
        strOFInstruction2[count3] = '\0';
        toUpperCase(strOFInstruction2);
        if(argv[2][0] == '1' || argv[2][0] == '2'){
            cout << " " << strOFInstruction2 ;
        }
        if(readFromFile[i][z] == ' ')
        {
        for(z; readFromFile[i][z] != '\0' && 
            readFromFile[i][z] != ';' &&
            flag == true; ++z )
        {
            if(readFromFile[i][z] != ' ' && 
                readFromFile[i][z] != ';' )
            {   // Parameter error
                cerr << endl<< "Invalid parameter!!"<<endl;
                i=row-1;
                flag = false;
            }
        }
    }    
    if(flag == true){
        if(argv[2][0] == '1' || argv[2][0] == '2'){
            cout << "   ";
            cout << "    R1 = " << reg[0] << " R2 = " << reg[1] 
                << " R3 = " << reg[2] << " R4 = " << reg[3] 
                 << " R5 = " << reg[4] ;
        }
        
        cout << endl ; 
        if(argv[2][0] == '1' || argv[2][0] == '2')
            cout << endl; 
            print(address,reg,strOFInstruction2); // for print
        }
    }
    return flag;
}
int parseJump(string* readFromFile,int i,
    int row,char strOFInstruction[100],
    char strOFInstruction2[100],char strOFInstruction3[100],
    char ** argv,int* reg,int intFromString,int t){

    bool flag =true; //If it is false , quit from program
    int count3=0,count4=0,k,z,j; // point and counter
    for(k=t; readFromFile[i][k] == ' '; ++k); // Ignore new space
    //Parameter error
    if(readFromFile[i][k] == ','){
        cerr << endl<< "Invalid parameter!!"<<endl;
        i=row-1; // error
        flag = false;
    }
                    
    if(flag == true)
    {
        if(readFromFile[i][k] == 'R' || readFromFile[i][k] == 'r' )
        { // If first parameter is register
                           
            for(z=k ; readFromFile[i][z] != ',' && 
                    readFromFile[i][z] != ' '; ++z )
            { 
            //read first parameter and assign char array
                strOFInstruction2[count3] = readFromFile[i][z];

                ++count3;
            }

            strOFInstruction2[count3] = '\0';

            toUpperCase(strOFInstruction2); //Case sensitive
            if(argv[2][0] == '1' || argv[2][0] == '2'){
                cout << " " << strOFInstruction2 << ", " ;
            }

            if(readFromFile[i][z] == ' ')
            {   //Parameter error
                for(z; readFromFile[i][z] != ',' && flag == true; ++z )
                {
                    if(readFromFile[i][z] != ' ' )
                    {
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        i=row-1;
                        flag = false;
                    }
                }
            }

            for(z=z+1;readFromFile[i][z] == ' '; ++z );//Ignore new line

            if(flag == true)
            {
                if(readFromFile[i][z]==';'&&readFromFile[i][z]=='\0'){
                    cerr << endl<< "Invalid parameter!!"<<endl;
                    i=row-1; // print error and quit from program
                    flag = false;
            }
                                
            if(flag == true)
            {
                for (j = z; readFromFile[i][j] != ';'  && 
                            readFromFile[i][j] != '\0' && 
                            readFromFile[i][j] != ' '; ++j )
                {
                //read second parameter and assign char array
                strOFInstruction3[count4] = readFromFile[i][j];

                ++count4;
                                        
                }

                strOFInstruction3[count4] = '\0';

                intFromString = atooi(strOFInstruction3); 
                // Turn integer from char array
                if(argv[2][0] == '1' || argv[2][0] == '2'){

                    cout <<  intFromString ;
                }
                if(readFromFile[i][j] == ' ')
                {
                    for(j; readFromFile[i][j] != ';' && 
                            readFromFile[i][j] != '\0' ; ++j )
                    {   // Parameter Error
                        if(readFromFile[i][j] != ' ' )
                        {
                            cerr << endl<< "Invalid parameter!!"<<endl;
                            i=row-1;
                            flag=false;
                        }
                    }                    
                        
                }
                //If LineAdress entered wrong
                if((intFromString < 1) )
                {   
                    cerr << endl<<  "Invalid line address!!" << endl;
                    i = row -1;
                    flag = false;
                }
                else if(intFromString > row){
                    cerr << endl<<  "Invalid line address!!" << endl;
                    i = row -1;
                    flag = false;
                }
                else
                    i = jump(strOFInstruction,reg,strOFInstruction2,intFromString,i);
                    // line index
            }
        }
    }
    else
    {
                            
        if(readFromFile[i][k]==';'&&readFromFile[i][k]=='\0'){
            cerr << endl<< "Invalid parameter!!"<<endl;
            i=row-1;
            flag = false;
        }
        if(flag == true)
        {
            for(z=k ;readFromFile[i][z] != ';' && 
                    readFromFile[i][z] != '\0' ; ++z )
            { 
            //read  parameter and assign char array
                if(readFromFile[i][z] != ' ')
                {
                    strOFInstruction2[count3] = readFromFile[i][z];

                    ++count3;
                }
            }

            strOFInstruction2[count3] = '\0';
            if(argv[2][0] == '1' || argv[2][0] == '2'){

                cout << " " << strOFInstruction2 << " " ;
            }

            intFromString = atooi(strOFInstruction2);
            //If LineAdress entered wrong
            if((intFromString < 1) ) 
            {   // Parameter Error
                cerr << endl<<  "Invalid line address!!" << endl;
                i = row -1;
                flag = false;
            }
            else if(intFromString > row){
                cerr << endl<<  "Invalid line address!!" << endl;
                i = row -1;
                flag = false;                                }
            else
                i  = jump(strOFInstruction,reg,strOFInstruction2,intFromString,i)-1;
                                    
            cout << "  ";
            }
        }
    }
    return i;
}/*Print*/
void option(int* reg){
    cout << "   R1 = " << reg[0] << " R2 = " << reg[1] << " R3 = " 
         << reg[2] << " R4 = " << reg[3] << " R5 = " << reg[4];
}