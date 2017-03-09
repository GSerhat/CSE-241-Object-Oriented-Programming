/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BigramMap.h
 * Author: serhat
 *
 * Created on December 25, 2016, 7:30 PM
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include "Bigram.h"

#include <string>
#include <fstream>
#include <map>

using namespace std;

namespace SerhatGuzel{
    
    template <class T>
    class BigramMap : public Bigram<T>
    {
        public:
            
            BigramMap();
            BigramMap(int dataType);
            
            virtual void readFile(const char* filename) throw() override ;
                /*readFile: takes a filename as a string parameter, reads the file, calculates all the bigrams.
                Throws exceptions if there are problems with opening and reading the file.*/
            virtual int numGrams() const override ;
                /*numGrams: returns the total number of bigrams calculated so far.*/
            virtual int numOfGrams(T p1 , T p2) const override ;
                /*numOfGrams: takes two elements as bigrams and returns the number of that bigram read so
                far.*/
            virtual pair<T, T> maxGrams() const override;
                /*maxGrams: returns the bigram that has occurred most frequently.*/
            

            virtual void print(ostream& output) const  override;
                /*operator<< prints all the bigrams and their occurences in decreasing occurent order.
                 helper print function*/
            int getTotal() const;
            void setTotal(int _total);
        private:
            int _dataType;
            map<pair<T, T> ,int > myMap;
            pair<T,T> myPair;
            pair<T,T> tempPair;
            int totalBigramNumber=0;
    };
}

#endif /* BIGRAMMAP_H */

