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

//distance from x to the nearest integer: a triangle wave between 0 and 0.5
inline double Triangle(double x){
  return fabs(x - round(x));
}

//Blancmange (Takagi): triangle waves stacked into a fractal
//y = sum of Triangle(2^n x) / 2^n
inline double Blancmange(double x){
  double y = 0;
  double p = 1;

  for (int n = 0; n < 30; ++n)
  {
    y += Triangle(p * x) / p;
    p *= 2;
  }
  return y;
}

//sawtooth of decaying exponentials: y = e^(-3 (x mod 1))
inline double ExpSaw(double x){
  return exp(-3 * Mod(x, 1));
}

//mod 1 slicing an exponential into a fan of lines: y = e^x mod 1
inline double ExpMod(double x){
  return Mod(exp(x), 1);
}

//Weierstrass: continuous everywhere, smooth nowhere
//y = sum of 0.5^n cos(3^n pi x)
inline double Weierstrass(double x){
  double y = 0;
  double a = 1;
  double b = 1;

  for (int n = 0; n < 15; ++n)
  {
    y += a * cos(b * M_PI * x);
    a *= 0.5;
    b *= 3;
  }
  return y;
}

//Riemann: y = sum of sin(n^2 x) / n^2
inline double Riemann(double x){
  double y = 0;

  for (int n = 1; n <= 50; ++n)
  {
    y += sin(n * n * x) / (n * n);
  }
  return y;
}

//Cantor, the devil's staircase: flat almost everywhere, still climbs from 0 to 1
inline double Cantor(double x){
  double y = 0;
  double p = 0.5;
  int digit = 0;

  if (x <= 0) return 0;
  if (x >= 1) return 1;

  //x in base 3: a digit 1 ends it, a digit 2 counts as a binary 1
  for (int n = 0; n < 40; ++n)
  {
    x *= 3;
    digit = (int) floor(x);
    x -= digit;

    if (digit == 1)
    {
      y += p;
      break;
    }
    if (digit == 2)
    {
      y += p;
    }
    p /= 2;
  }
  return y;
}

//heart: y = x^(2/3) + 0.9 sqrt(3.3 - x^2) sin(10 pi x)
inline double Heart(double x){
  return cbrt(x * x) + 0.9 * sqrt(3.3 - x * x) * sin(10 * M_PI * x);
}

//square wave from its first 8 Fourier terms
//y = 4/pi * sum of sin((2k-1) x) / (2k-1)
inline double Square(double x){
  double y = 0;

  for (int k = 1; k <= 8; ++k)
  {
    y += sin((2 * k - 1) * x) / (2 * k - 1);
  }
  return 4 / M_PI * y;
}

//y = sin(x) / x
inline double Sinc(double x){
  if (x == 0) return 1;
  return sin(x) / x;
}

//Bessel function of the first kind, order 0: a drum head
inline double Bessel(double x){
  return j0(x);
}

//Gamma: the factorial for any x, Gamma(n) = (n-1)!
inline double Gamma(double x){
  return tgamma(x);
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
