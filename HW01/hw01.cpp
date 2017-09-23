/* 
 * File:   hw01.cpp
 * Author: Serhat Güzel
 *
 * Created on September 26, 2016, 10:57 PM
 */

#include <iostream>
#include <fstream> /*File Operations*/
#include <string>

using namespace std;

void print(int* reg ,char* str); /*Print the given value*/
int* move(int* reg ,char* str1 ,char* str2 ,int inFromString);
/*Move from register to register or from constant to register*/
int* sub(int* reg ,char* str1 ,char* str2 ,int inFromString);
/*Subtraction from register until register or constant*/
int* add(int* reg ,char* str1 ,char* str2 ,int inFromString);
/*Addition from register until register or constant*/
int jump(int* reg ,char* str ,int inFromString,int i);
/*Jump other line */
int atooi(char* str);
/*Turn from character array to integer*/
char* toUpperCase(char* str);
/*Case sensitive*/
void readInstructions(string* readFromFile,int row,
                      string line,int reg[],int size,int argc, char** argv);
/*Basic operations*/
void option(int* reg);/*Print*/

int main(int argc, char** argv) 
{
    int NUM_OF_REGISTER=5,m; /*Register array size and point*/
    string line;  /*read from file*/
    string readFromFile[200]; /*General read from file*/
    int reg[NUM_OF_REGISTER],row=0;  /*Register array and  file line*/
    fstream inputStream(argv[1]);
    /*Initialize register array*/
    for(int j= 0 ; j<NUM_OF_REGISTER ; ++j)
        reg[j]=0;
    /*File operations-Open file*/
    inputStream.is_open();
    // Read from file 
    while(getline(inputStream,line) )
    {
        readFromFile[row] = &line[0];   
        
        ++ row;
        
        if(inputStream.eof())
            break ; 
    }/*If argument entered lower or bigger than 3*/
    if(argc != 3){
            cerr << "Invalid argument!!" << endl;
            
            return 0;
    }
    inputStream.close();
    // Basic operations
    readInstructions(readFromFile,row,line,reg,NUM_OF_REGISTER,argc,argv);
    
    return 0;
}
/*Move from register to register or from constant to register*/
int* move(int* reg ,char* str1 ,char* str2 ,int inFromString)
{   
    char buffer1[2],buffer2[2]; // Which register value
    int z,k; //for turn string to integer

    buffer1[0] = str1[1]; // Is it r1,r2,r3,r4,r5 ?
    buffer1[1] = '\0';
    z = atooi(buffer1); //for turn string to integer
    // is register or constant?
    if(inFromString != -9998) //If value didn't changed
        reg[z-1] = inFromString; // move from constant to register 
    
    else
    {   
        buffer2[0] = str2[1]; // Is it r1,r2,r3,r4,r5 ?
        buffer2[1] = '\0';
        k = atooi(buffer2); //for turn string to integer
        reg[k-1] = reg[z-1]; // move from register to register 
    } 
    
    return reg;
}
/*Print the given value*/
void print(int* reg ,char* str)
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
        cout << reg[z-1]  ;
    
}
/*Subtraction from register until register or constant*/
int* sub(int* reg ,char* str1 ,char* str2 ,int inFromString)
{
    char buffer1[2],buffer2[2]; // Which register value
    int z,k; //for turn string to integer

    buffer1[0] = str1[1]; // Is it r1,r2,r3,r4,r5 ?
    buffer1[1] = '\0';
    z = atooi(buffer1); //for turn string to integer
    // Subtraction from constant to register 
    if(inFromString != -9998) //If value didn't changed
        reg[z-1] = reg[z-1] - inFromString; 

    
    else
    {   
        buffer2[0] = str2[1]; // Is it r1,r2,r3,r4,r5 ?
        buffer2[1] = '\0';
        k = atooi(buffer2); //for turn string to integer
        reg[z-1] = reg[z-1] - reg[k-1];
        // Subtraction from register to register 
    } 
    
    return reg;
}
/*Addition from register until register or constant*/
int* add(int* reg ,char* str1 ,char* str2 ,int inFromString)
{
    char buffer1[2],buffer2[2]; // Which register value
    int z,k; //for turn string to integer

    buffer1[0] = str1[1]; // Is it r1,r2,r3,r4,r5 ?
    buffer1[1] = '\0';
    z = atooi(buffer1); //for turn string to integer
    // Addition from constant to register 
    if(inFromString != -9998) //If value didn't changed
        reg[z-1] = reg[z-1] + inFromString;
    
    else
    {   
        buffer2[0] = str2[1]; // Is it r1,r2,r3,r4,r5 ?
        buffer2[1] = '\0';
        k = atooi(buffer2); //for turn string to integer
        reg[z-1] = reg[z-1] + reg[k-1];
        // Addition from register to register  
    } 
    
    return reg;
}
/*Jump other line */
int jump(int* reg ,char* str ,int inFromString, int i)
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

        if(reg[z-1] == 0) // If reg is zero
            result = inFromString-2;
        else
            result = i; 
    }
    
    return result;
}
/*Turn from character array to integer*/
int atooi(char* str)
{
    double total = 0.0; 
    //Read until end of line
    for (int i = 0; str[i] != '\0'; ++i){
        
        if(str[i] == '-')
            //If it have to -
            (total = -(2.0 / 10));
        
        else
            total = total*10 + str[i] - '0';// Turn to integer
    }
   
    return total;
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
/*Basic operations*/
void readInstructions(string* readFromFile,int row,string line,
                        int reg[],int size,int argc, char** argv)
{

    char strOFInstruction[100],strOFInstruction2[100],strOFInstruction3[100];
    /*Division Instruction*/
    int  count2,count3,count4; /*Flag-Counter*/
    int z,intFromString; //For point and turn from string to integer
    bool flag =true;
    // Loop lrow
    for(int i=0; i < row ; ++ i)
    {
        count2 = 0;
        intFromString = -9998; // Flag value
        if(argv[2][0] == '1') // If option is 1
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
            if(readFromFile[i][t] == ' '|| readFromFile[i][t] == '\0' )
            {
                strOFInstruction[count2] = '\0';
                
                toUpperCase(strOFInstruction); // case sensitive
                if(argv[2][0] == '1')
                    cout << strOFInstruction;
                
                //If Instruction is MOV
                if(static_cast<string>(strOFInstruction) == "MOV" )
                {
                    count3 =0;

                    for(k=t; readFromFile[i][k] == ' '; ++k);
                        
                    if(readFromFile[i][k] == ','){
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        i=row-1;
                        flag = false;
                    }
                    if(flag == true){
                        for(z=k; readFromFile[i][z] != ',' && 
                                 readFromFile[i][z] != ' '; ++z )
                        { 
                             //read first parameter and assign char array.
                            strOFInstruction2[count3] = readFromFile[i][z];

                            ++count3;
                            
                        }
                        strOFInstruction2[count3] = '\0';
                        toUpperCase(strOFInstruction2);
                        if(argv[2][0] == '1'){
                            cout << " " << strOFInstruction2 << ", " ;
                        }
                        if(readFromFile[i][z] == ' ')
                        {
                           
                            //Parameter error
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
                        if(flag == true){
                            for(z=z+1;readFromFile[i][z] == ' '; ++z );
                            // ıgnore new space

                            if(readFromFile[i][z] == ';' && readFromFile[i][z] == '\0'){
                                cerr << endl<< "Invalid parameter!!"<<endl;
                                i=row-1;
                                flag = false;
                            }
                            
                            count4 = 0;
                            if(flag == true){
                                int n;
                                for(n=z;readFromFile[i][n] != ' ' && 
                                    readFromFile[i][n] != ';' && 
                                    readFromFile[i][n] != '\0'; ++n )
                                {
                                    //read second parameter and assign char array.
                                    strOFInstruction3[count4] = readFromFile[i][n];

                                    ++count4;
                                }
                               
                                strOFInstruction3[count4] = '\0';
                                toUpperCase(strOFInstruction3); // case sensitive
                               
                                // second parameter not register,it is constant
                                if(static_cast<string>(strOFInstruction3) != "R1" &&
                                   static_cast<string>(strOFInstruction3) != "R2" && 
                                   static_cast<string>(strOFInstruction3) != "R3" && 
                                   static_cast<string>(strOFInstruction3) != "R4" && 
                                   static_cast<string>(strOFInstruction3) != "R5" )
                                {
                                    intFromString = atooi(strOFInstruction3);
                                    if(argv[2][0] == '1'){
                                        cout << intFromString ;
                                    }
                                }
                                else
                                {
                                    if(argv[2][0] == '1')
                                        cout << strOFInstruction3 ;
                                    
                                } 
                                 
                                move(reg,strOFInstruction2,strOFInstruction3,intFromString);
                                
                                for (j = n; readFromFile[i][j] != ';' && 
                                    readFromFile[i][j] != '\0' && flag == true; ++j )
                                {
                                    if(readFromFile[i][j] != ' ')
                                    {   //error parameter
                                        cerr <<endl<< "Invalid parameter!!"<<endl;
                                        i=row-1;
                                        flag = false;
                                    }
                                }
                            }
                        }
                    }
                    
                }
                //If Instruction is PRN
                else if(static_cast<string>(strOFInstruction) =="PRN")
                {
                    count3 =0;
                    for(k=t; readFromFile[i][k] == ' '; ++k);//Ignore new space

                    if(readFromFile[i][k] == ';' && readFromFile[i][k] =='\0'){
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        i=row-1;
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
                        if(argv[2][0] == '1'){
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
                            if(argv[2][0] == '1'){
                                cout << "   ";
                                cout << "    R1 = " << reg[0] << " R2 = " << reg[1] 
                                     << " R3 = " << reg[2] << " R4 = " << reg[3] 
                                     << " R5 = " << reg[4] ;
                            }
                            cout << endl ; 
                            if(argv[2][0] == '1')
                                cout << endl; 
                            print(reg,strOFInstruction2);
                        }
                    }

                }
                 //If Instruction is SUB
                else if(static_cast<string>(strOFInstruction) == "SUB") 
                {
                    count3 =0;

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
                        if(argv[2][0] == '1'){
                            cout << " " << strOFInstruction2 << ", " ;
                        }

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
                            
                        count4 = 0;
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

                            //cout << strOFInstruction3 << "a" << endl;
                            if(static_cast<string>(strOFInstruction3) != "R1" &&
                               static_cast<string>(strOFInstruction3) != "R2" && 
                               static_cast<string>(strOFInstruction3) != "R3" &&
                               static_cast<string>(strOFInstruction3) != "R4" && 
                               static_cast<string>(strOFInstruction3) != "R5" )
                            {
                                intFromString = atooi(strOFInstruction3);
                                if(argv[2][0] == '1'){
                                    cout << intFromString ;
                                }
                            }
                            else{
                                if(argv[2][0] == '1'){
                                    cout << strOFInstruction3 ;
                                }
                            } 
                                
                            
                            sub(reg,strOFInstruction2,strOFInstruction3,intFromString);
                            

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
                //If Instruction is ADD  
                else if(static_cast<string>(strOFInstruction) =="ADD") 
                {
                    count3 =0;

                    for(k=t; readFromFile[i][k] == ' '; ++k);
                        //Parameter error
                    if(readFromFile[i][k] == ','  ){
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        i=row-1;
                       flag = false;
                    }
                    if(flag == true)
                    {
                        for(z=k; readFromFile[i][z] != ',' && 
                                 readFromFile[i][z] != ' '; ++z )
                        {   //read first parameter and assign char array
                            strOFInstruction2[count3] = readFromFile[i][z];

                            ++count3;
                        }
                        
                        strOFInstruction2[count3] = '\0';

                        toUpperCase(strOFInstruction2); // Case sensitive
                        if(argv[2][0] == '1'){
                            cout << " " << strOFInstruction2 << ", " ;
                        }

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
                        if(flag == true)
                        {
                            for(z=z+1;readFromFile[i][z] == ' '; ++z );
                            //Ignore new space
                            if(readFromFile[i][z] == ';' && readFromFile[i][z] == '\0' ){
                                cerr << endl<< "Invalid parameter!!"<<endl;
                                i=row-1;
                                flag = false;
                            }
                                
                            count4 = 0;
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
                                
                                if(static_cast<string>(strOFInstruction3) != "R1" &&
                                   static_cast<string>(strOFInstruction3) != "R2" && 
                                   static_cast<string>(strOFInstruction3) != "R3" &&
                                   static_cast<string>(strOFInstruction3) != "R4" && 
                                   static_cast<string>(strOFInstruction3) != "R5" )
                                {   //If second parameter is constant
                                    intFromString = atooi(strOFInstruction3);
                                    if(argv[2][0] == '1'){
                                        cout << intFromString ;
                                    }
                                }
                                else{
                                    if(argv[2][0] == '1'){
                                        cout << strOFInstruction3 ;
                                    }
                                } 
                                add(reg,strOFInstruction2,strOFInstruction3,intFromString);

                                if(readFromFile[i][j] == ' ')
                                {
                                   for(j;readFromFile[i][j]!=';' && 
                                         readFromFile[i][j]!='\0' &&
                                         flag == true ;++j)
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
                }
                //If Instruction is JMP
                else if(static_cast<string>(strOFInstruction) =="JMP")
                {   
                    for(k=t; readFromFile[i][k] == ' '; ++k);
                    //Parameter error
                    if(readFromFile[i][k] == ','){
                        cerr << endl<< "Invalid parameter!!"<<endl;
                        i=row-1;
                        flag = false;
                    }
                    
                    count3=0;
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
                            if(argv[2][0] == '1'){
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
                                    i=row-1;
                                    flag = false;
                                }
                                
                                count4 = 0;
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
                                    if(argv[2][0] == '1'){

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
                                        i = jump(reg,strOFInstruction2,intFromString,i);
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
                                for(z=k ; readFromFile[i][z] != ';' && 
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
                                if(argv[2][0] == '1'){

                                    cout << " " << strOFInstruction2 << ", " ;
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
                                    i  = jump(reg,strOFInstruction2,intFromString,i)-1;
                                
                                cout << "  ";
                            }

                        }
                    }
                }
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
            else if(argv[2][0] != '0'){
                cout<<"Invalid argument" <<endl;
                i= row;
                break;
            }
        }
    }
    /*If Option is 0*/
    if(argv[2][0] == '0')
        cout << endl<< "R1 = " << reg[0] << " R2 = " << reg[1] << " R3 = " 
             << reg[2] << " R4 = " << reg[3] << " R5 = " << reg[4] ;
            
    cout << endl;
} /*Print*/
void option(int* reg){
    cout << "   R1 = " << reg[0] << " R2 = " << reg[1] << " R3 = " 
         << reg[2] << " R4 = " << reg[3] << " R5 = " << reg[4] ;
}

