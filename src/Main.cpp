#include <iostream>
#include <cstdlib>

#include "MathPloText.hpp"

using namespace std;


int main(int argc, char *argv[])
{
  MathPloText *math = new MathPloText();

  math->SetConfig();

  math->SetMatrix();

  math->PlotGraph(Pow, 2);
  
  return 0;
}
