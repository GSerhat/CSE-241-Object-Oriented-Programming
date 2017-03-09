/* 
 * File:   BigramDyn.h
 * Author: serhat
 *
 * Created on December 25, 2016, 7:46 PM
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H
#include "Bigram.h"

#include <string>
#include <fstream>
using namespace std;

namespace SerhatGuzel{
    
    template <class T>
    class BigramDyn : public Bigram<T>
    {
        public:
            
            BigramDyn();
            BigramDyn(int _dataType);
            virtual void readFile(const char* filename) throw() override;
            /*readFile: takes a filename as a string parameter, reads the file, calculates all the bigrams.
            Throws exceptions if there are problems with opening and reading the file.*/
            virtual int numGrams() const override;
            /*numGrams: returns the total number of bigrams calculated so far.*/
            virtual int numOfGrams(T p1 , T p2) const override;
            /*numOfGrams: takes two elements as bigrams and returns the number of that bigram read so
                far.*/
            virtual pair<T,T> maxGrams() const override;
            /*maxGrams: returns the bigram that has occurred most frequently.*/
            virtual void print(ostream& str) const override;
            /*operator<< prints all the bigrams and their occurences in decreasing occurent order.
            helper print function*/
             ~BigramDyn();
            int getTotalDyn() const;
            void setTotalDyn(int _total);
        
         private:
             int _dataType;
             pair<pair<T,T>, int> * myArr = nullptr;
             pair<T,T> myPair;
             pair<T,T> tempPair;
             int capacity =0;
             int totalBigramNumber=0;
             int size =0;
    };
}

#endif /* BIGRAMDYN_H */

