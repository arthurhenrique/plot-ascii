#include <iostream>

#include "MathPloText.h"

using namespace std;

int main(int argc, char *argv[])
{
    MathPloText *math = new MathPloText();

    math->setMatrix();

    math->plotGraph();
    
    return 0;

}