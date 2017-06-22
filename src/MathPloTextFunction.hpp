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

#endif //_MATH_PLO_TEXT_FUNCTION_HPP_
