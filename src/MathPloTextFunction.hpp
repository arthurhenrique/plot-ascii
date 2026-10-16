#ifndef _MATH_PLO_TEXT_FUNCTION_HPP_
#define _MATH_PLO_TEXT_FUNCTION_HPP_


#include <stdio.h>
#include <cmath>
#include <functional>


inline double Add(double a, double b){
  return a+b;
}

inline double Sub(double a, double b){
  return a-b;
}

inline double Mult(double a, double b){
  return a*b;
}

inline double Div(double a, double b){
  return a/b;
}

inline double Pow(double a, double b){
  return pow(a,b);
}

inline double Combiner(double a, double b, std::function<double (double,double)> func){
  return func(a,b);
}

//modulo that is always positive: Mod(-0.25, 1) = 0.75
inline double Mod(double a, double b){
  return a - b * floor(a / b);
}

//y = (1 - 2*floor(2*(x mod 1))) * |sin(pi*x/4)| * x + |x| - 10
inline double Matharium(double x){
  return (1 - 2 * floor(2 * Mod(x, 1))) * fabs(sin(M_PI * x / 4)) * x + fabs(x) - 10;
}

//y = sin(6.5x)^2 / cosh(x/2.6)
inline double SinCosh(double x){
  return pow(sin(6.5 * x), 2) / cosh(x / 2.6);
}

//derivative of func at x
inline double Derivative(std::function<double (double)> func, double x){
  double h = 1e-5;
  return (func(x + h) - func(x - h)) / (2 * h);
}

//integral of func from a to b (Simpson's rule)
inline double Integral(std::function<double (double)> func, double a, double b){
  int    n   = 200;
  double h   = (b - a) / n;
  double sum = func(a) + func(b);

  for (int i = 1; i < n; ++i)
  {
    sum += func(a + i * h) * (i % 2 == 1 ? 4 : 2);
  }
  return sum * h / 3;
}

#endif //_MATH_PLO_TEXT_FUNCTION_HPP_
