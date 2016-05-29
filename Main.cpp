#include <iostream>

#include "MathPloText.h"

using namespace std;

int main()
{   
    int i = 0;
    int y = 0;
    int x = 0;

    ponto p[(MAX * 2) * (MAX * 2)] = {0};
    

    for (x = MAX ; x > MAX * -1; --x)
    {
        for (y = (MAX * -1) ; y < MAX; ++y)
        {
            p[i].x = x;
            p[i].y = y;
            ++i;
        }
    } 

    i = 0;

    //plot text
    for (x = MAX ; x > MAX * -1; --x)
    {
        for (y = (MAX * -1) ; y < MAX; ++y)
        {
            if(x == p[i].x && y == MathPloText::fPow2(p[i].x))
            {
                cout << "X";
            }
            cout << ".";
            ++i;
        }
        cout << endl;
    }
    
    return 0;
}