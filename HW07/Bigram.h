/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bigram.h
 * Author: serhat
 *
 * Created on December 25, 2016, 4:32 PM
 */

#ifndef BIGRAM_H
#define BIGRAM_H
#include <iostream>
using namespace std;

namespace SerhatGuzel{
    template <class T>
    class Bigram
    {

    public:
        
        virtual void readFile(const char* filename)= 0;
        /*readFile: takes a filename as a string parameter, reads the file, calculates all the bigrams.
        Throws exceptions if there are problems with opening and reading the file. This function is a pure abstract.*/
        virtual int numGrams() const  = 0;
        /*numGrams: returns the total number of bigrams calculated so far.*/
        virtual int numOfGrams(T p1 , T p2) const = 0;
        /*numOfGrams: takes two elements as bigrams and returns the number of that bigram read so
        far.*/
        virtual pair<T,T> maxGrams() const = 0;
        /*maxGrams: returns the bigram that has occurred most frequently.*/
        virtual void print(ostream& output) const = 0;
        /*operator<< prints all the bigrams and their occurences in decreasing occurent order.
         helper print function*/
        friend ostream& operator <<(ostream& output , const Bigram& big){
            big.print(output);
            return output;
        }

    };
}

#endif /* BIGRAM_H */

