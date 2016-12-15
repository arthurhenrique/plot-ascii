#ifndef _MATH_PLO_TEXT_H_
#define _MATH_PLO_TEXT_H_

#define MAX_DEFAULT 8

#include <stdio.h>
#include <cmath>

#include "MathPloTextStruct.hpp"

class MathPloText
{
public:
    //Costructor
    MathPloText();

    //Destructor
    ~MathPloText();
    
    //TODO add in another class with only math functions
    static int getPow(int x, int power);
    
    //Add parameter and call function by address value 
    void plotGraph();

    //Init a matrix 
    void setMatrix(int length = MAX_DEFAULT);    

private:
    //Configuration
    void setConfig();

    //
    int mLength;

    Point* mPoint;

};

#endif //_MATH_PLO_TEXT_H_