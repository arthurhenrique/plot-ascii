#include <iostream>
#include <stdio.h>
#include "MathPloText.h"

using namespace std;

int main()
{   
    int i = 0;
    int y = 0;
    int x = 0;

    ponto p[(MAX * 2) * (MAX * 2)] = {0};
    
    //TODO Function
    /*
    PLOT
    
    (x,  y)    
    (-1, 1) (0, 1) (1, 1)  
    (-1, 0) (0, 0) (1, 0)
    (-1,-1) (0,-1) (1,-1)


    */

    for (y = MAX ; y > (MAX * -1); --y)
    {
        for (x = (MAX * -1) ; x < MAX; ++x)
        {
            p[i].x = x;
            p[i].y = y;
            ++i;
        }
    } 

    
    i = 0;


    for (y = MAX ; y > (MAX * -1); --y)
    {
        for (x = (MAX * -1) ; x < MAX; ++x)
        {
            if(x == p[i].x && y == MathPloText::fPow(p[i].x,2))
            {
                printf("%3c", '#');
            }
            else
            {
                printf("%3c", '`');
            }
            ++i;
        }
        cout << endl;
    } 

    return 0;
}