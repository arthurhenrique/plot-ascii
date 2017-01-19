#include <iostream>

#include "MathPloTextFunction.hpp"

using namespace std;

/* Prints a exponencial function
f(x) = x ^ power
(x, x^power) 
*/
static int MathPloTextFunction::GetPow(int xPoint, int power)
{
  return pow(xPoint, power);
}