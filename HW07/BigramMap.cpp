/* 
 * File:   BigramMap.cpp
 * Author: serhat
 * 
 * Created on December 25, 2016, 7:30 PM
 */
#include <iostream>
#include <map>
#include "BigramMap.h"

using namespace std;

namespace SerhatGuzel{
    template <class T>
    BigramMap<T>::BigramMap() 
    {}
    template <class T>
    BigramMap<T>::BigramMap(int dataType) 
    {
        _dataType = dataType;
    }
    template<class T>
    void BigramMap<T>:: readFile(const char* filename) throw()
    {
        fstream input,input2,testFile,inputBadData;
        T a,b,k,test;
        int count=0,testCount=0;
        
        input.open(filename);
        if(input.fail())
            throw runtime_error("File did not opened"); /*Exception */
        input2.open(filename);
        testFile.open(filename);

        while(testFile){
            testFile >> test;
            
            testCount++;
        }
        testCount -=1; /*Dosyanin sonuna gelince 2. defa sayiyor */
        testFile.close();
        
        if(testCount<=1){
            throw runtime_error("Missing Data Error"); /*Exception */
        }
        inputBadData.open(filename);
        bool flag = true;
        while(flag){
            T badData;
            if(!(inputBadData >> badData) || inputBadData.eof()){
                if(inputBadData.eof())
                    flag = false;
                else{
                    flag = false;
                    throw runtime_error("Bad Data"); /*Exception */
                }
            }
        }
        inputBadData.close();
        /*Dosayadan okuyup map ın içine atiyoruz. Key degerlerine gore valuelarimizi denklestirdik.*/
        while(input2){
            input2>>k;
            
            count++;
        }
        int i=1;
        myMap[tempPair] = 1;
        input >> a;
        
        while(i<count-1){
            
            input >> b;
            tempPair = make_pair(a,b);
            myPair=make_pair(a,b);
            myMap[myPair]++;
            if(myMap[myPair] > myMap[tempPair]){
                tempPair = make_pair(a,b);
            }
            setTotal(1);
            ++i;

            a=b; 
        }
       
        
        
        input.close();
        input2.close();

    }
    template <class T>
    int BigramMap<T> ::getTotal() const{
        return totalBigramNumber;
    }
    template <class T>
    void BigramMap<T>::setTotal(int _total){
        totalBigramNumber = _total+totalBigramNumber;
    }
    template <class T>
    int BigramMap<T>:: numGrams() const  /*Toplam pair sayisi*/
    {
        cout << "numGrams is " ;
        return getTotal();
    }
    template <class T>
    int BigramMap<T>:: numOfGrams(T p1 , T p2)  const /*Istenen ciftten kac taneye sahibiz*/
    {
        int result =0;
        pair<T,T> numPair = make_pair(p1,p2);
        
        auto res = myMap.find(make_pair(p1,p2));
        if(res != myMap.end()){

            result =res->second;
        }
        
        
        cout << "numOfGrams is " ;
        return result;
    }
    template <class T>
    pair<T, T> BigramMap<T>:: maxGrams() const /*varolan pairlerden en cok tekrar eden*/
    {
        cout << "max gram is ";
        return tempPair;
    }
    template <class T>
    void BigramMap<T>:: print(ostream& output) const /*Azalan siraya gore bastirdik.*/
    {
        int temp2 = totalBigramNumber+1 ;
        int *arr = new int[temp2];
        pair<T,T> *pairArr = new  pair<T,T>[temp2];
        
        int i=0;
        
        for( auto p = ++myMap.begin() ; p != myMap.end() ; ++p){
            
            arr[i] = p->second;
            pairArr[i] = p->first;
            
            ++i;
        }
        int j;
	  int temp;
        pair<T,T> localPair;
	  for (int k = 0; k < i; k++){
		j = k;
		
		while (j > 0 && arr[j] < arr[j-1]){
			  
                    temp = arr[j];
                    arr[j] = arr[j-1];
                    arr[j-1] = temp;
                    localPair = pairArr[j];
                    pairArr[j] = pairArr[j-1];
                    pairArr[j-1] = localPair;
		
                    --j;
                }
	  }
        int l=i-1;
        
        for(int t =0;t <l ; ++t){
            for( auto p = ++myMap.begin() ; p != myMap.end() ; ++p){
                
//                
                    output <<"pair<"<< pairArr[l].first <<","<< pairArr[l].second<<">"  ;
                    output << " =  "<< arr[l]<<endl;
//                
            --l;
            }
        }
        
        
    }
}

