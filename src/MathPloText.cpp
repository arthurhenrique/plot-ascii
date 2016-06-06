#include <iostream>

#include "MathPloText.h"

using namespace std;

/* Prints a exponencial function
f(x) = x ^ power
(x, x^power) 
*/
static int MathPloText::getPow(int x, int power)
{
    return pow(x, power);
}

/*
Fill matrix with values
        (x, y)
(-1, 1) (0, 1) (1, 1)
(-1, 0) (0, 0) (1, 0)
(-1,-1) (0,-1) (1,-1)
*/
void MathPloText::setMatrix()
{

    int i = 0;
    int y = 0;
    int x = 0;

    for ( y = MAX; y > (MAX * -1); --y )
    {
        for ( x = (MAX * -1) ; x < MAX; ++x )
        {
            p[i].x = x;
            p[i].y = y;
            ++i;
        }
    }
}
/* plot graph using defined function.

*/
void MathPloText::plotGraph()
{

    int i = 0;
    int y = 0;
    int x = 0;

    for ( y = MAX; y > (MAX * -1); --y )
    {
        for ( x = (MAX * -1); x < MAX; ++x )
        {
            //(x,y) will be represent by especial char bellow
            if ( x == p[i].x &&
                 y == MathPloText::getPow(p[i].x,2) )
            {
                printf("%3c", '#');
            }
            //y-axes will be represent by especial char bellow
            else if ( x == 0 )
            {
                printf("%3c",'|');
            }
            //x-axis will be represent by especial char bellow
            else if ( y == 0 )
            {
                printf("%3c",'-');
            }
            //complete this graph with this especial char bellow
            else
            {
                printf("%3c", '`');
            }
            ++i;
        }
        cout << endl;
    }
}

MathPloText::MathPloText()
{

}


MathPloText::~MathPloText()
{
    
}
