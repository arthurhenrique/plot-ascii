#include <iostream>
#include <cstdlib>

#include "MathPloText.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  MathPloText *math = new MathPloText();

  math->SetConfig('\43');

  math->SetMatrix(15);

  math->PlotGraph();
  
  return 0;

}