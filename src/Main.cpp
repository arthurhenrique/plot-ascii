#include <iostream>
#include <cstdlib>

#include "MathPloText.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    MathPloText *math = new MathPloText();

    math->setMatrix(10);

    math->plotGraph();
    
    return 0;

}