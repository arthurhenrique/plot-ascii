#include <iostream>

#include "MathPloText.hpp"

using namespace std;


MathPloText::MathPloText()
{
    mLength = 0; 
}


MathPloText::~MathPloText()
{
    
}

/* Prints a exponencial function
f(x) = x ^ power
(x, x^power) 
*/
static int MathPloText::getPow(int xPoint, int power)
{
    return pow(xPoint, power);
}

/* plot graph using defined function.

*/
void MathPloText::plotGraph()
{
    int count  = 0;
    int yPoint = 0;
    int xPoint = 0;
    int length = mLength;

    for ( yPoint = length; yPoint > (length * -1); --yPoint )
    {
        for ( xPoint = (length * -1); xPoint < length; ++xPoint )
        {
            //(xPoint,yPoint) will be represent by especial char bellow
            if ( xPoint == this->mPoint[count].x &&
                 yPoint == MathPloText::getPow(this->mPoint[count].x,2) )
            {
                printf("%3c", '#');
            }
            //yPoint-axes will be represent by especial char bellow
            else if ( xPoint == 0 )
            {
                printf("%3c",'|');
            }
            //xPoint-axis will be represent by especial char bellow
            else if ( yPoint == 0 )
            {
                printf("%3c",'-');
            }
            //complete this graph with this especial char bellow
            else
            {
                printf("%3c", '`');
            }
            ++count;
        }
        cout << endl;
    }
}


/*
Fill matrix with values
        (xPoint, yPoint)
(-1, 1) (0, 1) (1, 1)
(-1, 0) (0, 0) (1, 0)
(-1,-1) (0,-1) (1,-1)
*/
void MathPloText::setMatrix(int length)
{
    int count     = 0;
    int yPoint    = 0;
    int xPoint    = 0;
    int size      = length * length;
    mLength = length;

    this->mPoint = new Point[size];

    //Fill coordinator xPoint,y based on matrix
    for ( yPoint = length; yPoint > (length * -1); --yPoint )
    {
        for ( xPoint = (length * -1) ; xPoint < length; ++xPoint )
        {
            this->mPoint[count].x = xPoint;
            this->mPoint[count].y = yPoint;
            ++count;
        }
    }
}

void MathPloText::setConfig()
{

}

