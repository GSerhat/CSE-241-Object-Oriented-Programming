/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: serhat
 *
 * Created on December 30, 2016, 4:28 AM
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
using namespace std;

namespace SerhatGuzel{
    
    class Exception : public exception
    {
        
            virtual const char* what() const throw()
            {
                return "My exception happened";
            }
        
    };
}


#endif /* EXCEPTION_H */

