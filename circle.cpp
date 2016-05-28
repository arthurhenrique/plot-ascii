#include <iostream>
#include <cmath>
#define MAX 100

using namespace std;

struct ponto
{
    int x;
    int y;
};


/*

f(x) = x ^ 2
(x, x^2)

*/
int f(int x)
{
    return pow(x, 2);
}


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

    for (x = MAX ; x > MAX * -1; --x)
    {
        for (y = (MAX * -1) ; y < MAX; ++y)
        {
            if(x == p[i].x && y == f(p[i].x))
            {
                cout << "X";
            }
            cout << ".";
            //printf("(%3d, %3d)",p[i].x, p[i].y );
            ++i;
        }
        cout << endl;
    }
    
    return 0;
}