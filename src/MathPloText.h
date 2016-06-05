#ifndef _MATH_PLO_TEXT_H_
#define _MATH_PLO_TEXT_H_

#define MAX 10
#define SIZE (MAX * 2) * (MAX * 2)

#include <stdio.h>
#include <cmath>

#include "MathPloTextStruct.h"

class MathPloText
{
public:
    Point p[SIZE];

    MathPloText();
    ~MathPloText();
    static int getPow(int x, int power);
    void setMatrix();
    void plotGraph();
};

#endif //_MATH_PLO_TEXT_H_