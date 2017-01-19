#include <iostream>
#include <cstdlib>

#include "MathPloText.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  MathPloText *math = new MathPloText();

  math->SetMatrix(10);

  math->PlotGraph();
  
  return 0;

}