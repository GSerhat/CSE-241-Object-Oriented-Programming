/* 
 * File:   BigramDyn.cpp
 * Author: serhat
 * 
 * Created on December 25, 2016, 7:46 PM
 */

#include "BigramDyn.h"
#include <iostream>

using namespace std;

namespace SerhatGuzel{
    
    template <class T>
    BigramDyn<T>::BigramDyn()
    {}
    template <class T>
    BigramDyn<T>::BigramDyn(int dataType) 
    {
        _dataType = dataType;
    }
    template <class T>
    void BigramDyn<T>:: readFile(const char* filename) throw() 
     {
        fstream testFile,input,inputBadData;
        
        T a,b,k,test;
        int testCount=0;
        bool flag = true,boolPair;
        
        input.open(filename);
        
        testFile.open(filename);
        if(input.fail())
            throw runtime_error("File did not opened"); /*Exception*/
        
        while(testFile){
            testFile >> test;
            testCount++;
            
        }
        testCount -=1; /*Dosyanin sonuna gelince 2. defa sayiyor */
        if(testCount<=1){
            throw runtime_error("Missing Data Error"); /*Exception*/
        }
        
        inputBadData.open(filename);
        
        while(flag){
        
            T badData;
            
            if(!(inputBadData >> badData) || inputBadData.eof())
            {
                
                if(inputBadData.eof())
            
                    flag = false;
                else{
                    flag = false;
                    throw runtime_error("Bad Data"); /*Exception*/
                }
            }
            
            capacity++;
        }
        
        myArr = new pair<pair<T,T>,int> [capacity];
        /*Array icin dinamik yer ayirdik.*/
        
        myArr[capacity-1].second = 1;
        
        int i=0;
        int count=0;
        
        input>>a;
        /*Dosayadan okuyup arraya  attik.Daha sonra kac pair olduğunu belirliyouz.*/
        while(i<capacity-2){
        
            boolPair=false;
            input >> b;
            tempPair=make_pair(a,b);
            myPair=make_pair(a,b);
            
            for(int k=0;k<=count;++k){
            
                if(myArr[k].first.first == myPair.first && myArr[k].first.second == myPair.second ){
                    myArr[k].second++;
                    boolPair = true; /*ayni paire sahipsek*/
                }
            }
            
            if(boolPair == false){
                
                myArr[count].first.first = myPair.first;
                myArr[count].first.second = myPair.second;
                myArr[count].second++;
                count++; /*Pairleri ekledik.*/
                
            }
            
            setTotalDyn(1);/*Kac pair var*/
            ++i;

            a=b; 
        }
        
        int j=0;
        
        int max = myArr[j].second;
        /*pairler içinde maximum olani bulduk.*/
        for(j =1;j<count;++j){
            
            if(myArr[j].second > max ){
                max = myArr[j].second;
                tempPair.first = myArr[j].first.first;
               
                tempPair.second = myArr[j].first.second;
            }
        }
        
        size = count;
        
        input.close();
        
        testFile.close();
        inputBadData.close();
       
    }
    template <class T>
    int BigramDyn<T> ::getTotalDyn() const
    {
        return totalBigramNumber;
    }
    template <class T>
    void BigramDyn<T>::setTotalDyn(int _total)
    {
        totalBigramNumber = _total+totalBigramNumber;
    }
    template <class T>
    int BigramDyn<T>:: numGrams() const /*Toplam pair sayisi*/
    {
        cout << "numGrams is " ;
        return getTotalDyn();
    }
    template <class T>
    int BigramDyn<T>:: numOfGrams(T p1 , T p2) const /*Istenen ciftten kac taneye sahibiz*/
    {
        int result=0;
        for(int i=0;i<size;++i){
            if(myArr[i].first.first == p1 && myArr[i].first.second == p2){
                result =  myArr[i].second;
            }
        }
        
        cout << "numOfGrams is " ;
        return result;
    }
    template <class T>
    pair<T, T> BigramDyn<T>:: maxGrams() const /*varolan pairlerden en cok tekrar eden*/
    {
        cout << "max gram is ";
        
        return tempPair;
    } 
    template <class T>
    void BigramDyn<T> :: print(ostream& output) const/*Azalan siraya gore bastirdik.*/
    {
        int temp;
        pair<T,T> localPair;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
                    
                    if(myArr[i].second < myArr[j].second){
                        
                        temp =  myArr[i].second  ;
                        myArr[i].second  = myArr[j].second ;
                        myArr[j].second  =  temp;
                        localPair.first = myArr[j].first.first;
                        myArr[j].first.first = myArr[i].first.first;
                        myArr[i].first.first = localPair.first;
                        localPair.second = myArr[j].first.second;
                        myArr[j].first.second = myArr[i].first.second;
                        myArr[i].first.second = localPair.second;
                        }
                }
        }
        for(int t =size-1;t != -1 ; --t){
            
            output <<"pair<"<< myArr[t].first.first <<","<< myArr[t].first.second<<">"  ;
            output << " =  "<< myArr[t].second<<endl;
        }
    }
    template <class T>
    BigramDyn<T> :: ~BigramDyn() 
    {
           delete[]myArr;
    }
    
}
