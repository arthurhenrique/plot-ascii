#ifndef _MATH_PLO_TEXT_ARSENAL_HPP_
#define _MATH_PLO_TEXT_ARSENAL_HPP_

/*
More functions to plot: special functions, number theory, chaos,
fractals, noise and some shapes.
*/

#include <cmath>

#include "MathPloTextFunction.hpp"


//
//special functions
//

//Riemann zeta, by Euler-Maclaurin: zeta(2) = pi^2/6, pole at 1
inline double Zeta(double s){
  int    n   = 10;
  double sum = 0;

  if (s == 1) return NAN;

  for (int k = 1; k < n; ++k)
  {
    sum += pow(k, -s);
  }
  sum += pow(n, 1 - s) / (s - 1) + pow(n, -s) / 2;
  sum += s * pow(n, -s - 1) / 12;
  sum -= s * (s + 1) * (s + 2) * pow(n, -s - 3) / 720;
  return sum;
}

//Lambert W: the w with w e^w = x (Halley's method)
inline double LambertW(double x){
  double w = 0;

  if (x < -1 / M_E) return NAN;

  w = x < 1 ? x : log(x);

  for (int k = 0; k < 50; ++k)
  {
    double e = exp(w);
    double f = w * e - x;
    w -= f / (e * (w + 1) - (w + 2) * f / (2 * w + 2));
  }
  return w;
}

//Legendre polynomial P_n(x)
inline double Legendre(double n, double x){
  double p0 = 1;
  double p1 = x;
  double p2 = 0;

  if (n < 1) return 1;

  for (int k = 1; k < (int) n; ++k)
  {
    p2 = ((2 * k + 1) * x * p1 - k * p0) / (k + 1);
    p0 = p1;
    p1 = p2;
  }
  return p1;
}

//quantum harmonic oscillator, |psi_n(x)|^2 with Hermite polynomials
inline double Oscillator(double n, double x){
  double h0 = 1;
  double h1 = 2 * x;
  double h2 = 0;
  double h  = (int) n == 0 ? h0 : h1;

  for (int k = 1; k < (int) n; ++k)
  {
    h2 = 2 * x * h1 - 2 * k * h0;
    h0 = h1;
    h1 = h2;
    h  = h1;
  }

  return h * h * exp(-x * x) / (pow(2, n) * tgamma(n + 1) * sqrt(M_PI));
}

//pendulum period over the small swing period, for a swing of x radians
//T / T0 = 1 / agm(1, cos(x/2)), infinite at x = pi
inline double Pendulum(double x){
  double a = 1;
  double b = cos(x / 2);

  if (fabs(x) >= M_PI) return NAN;

  for (int k = 0; k < 30; ++k)
  {
    double m = (a + b) / 2;
    b = sqrt(a * b);
    a = m;
  }
  return 1 / a;
}

//
//number theory, on n = floor(x)
//

inline bool IsPrime(long n){
  if (n < 2) return false;

  for (long d = 2; d * d <= n; ++d)
  {
    if (n % d == 0) return false;
  }
  return true;
}

//how many primes up to x
inline double PrimeCount(double x){
  int count = 0;

  for (long n = 2; n <= (long) floor(x); ++n)
  {
    if (IsPrime(n)) ++count;
  }
  return count;
}

//Euler's totient: how many numbers up to n share no factor with n
inline double Totient(double x){
  long n = (long) floor(x);
  long result = n;

  if (n < 1) return NAN;

  for (long p = 2; p * p <= n; ++p)
  {
    if (n % p == 0)
    {
      while (n % p == 0) n /= p;
      result -= result / p;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}

//how many divisors n has
inline double Divisors(double x){
  long n = (long) floor(x);
  int count = 0;

  if (n < 1) return NAN;

  for (long d = 1; d <= n; ++d)
  {
    if (n % d == 0) ++count;
  }
  return count;
}

//sum of the digits of n
inline double DigitSum(double x){
  long n = (long) floor(fabs(x));
  int sum = 0;

  while (n > 0)
  {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

//Collatz: steps from n to 1, halving evens and taking 3n+1 of odds
inline double Collatz(double x){
  long n = (long) floor(x);
  int steps = 0;

  if (n < 1) return NAN;

  while (n != 1)
  {
    if (n % 2 == 0) n /= 2;
    else            n = 3 * n + 1;
    ++steps;
  }
  return steps;
}

//Mobius: 0 if n has a squared factor, else +1 or -1 by its number of primes
inline double Mobius(double x){
  long n = (long) floor(x);
  int sign = 1;

  if (n < 1) return NAN;

  for (long p = 2; p * p <= n; ++p)
  {
    if (n % p == 0)
    {
      n /= p;
      if (n % p == 0) return 0;
      sign = -sign;
    }
  }
  if (n > 1) sign = -sign;
  return sign;
}

//Mertens: running sum of Mobius, a random walk on the primes
inline double Mertens(double x){
  double sum = 0;

  for (long n = 1; n <= (long) floor(x); ++n)
  {
    sum += Mobius(n);
  }
  return sum;
}

//
//chaos: after the transient, a few more steps that change with x,
//so close values of x land on different points of the attractor
//

inline int Phase(double x){
  return (int) (Mod(x * 9973.0, 1) * 64);
}

//logistic map x -> r x (1 - x): order, period doubling, chaos
inline double Logistic(double r){
  double x = 0.3;
  int steps = 500 + Phase(r);

  for (int k = 0; k < steps; ++k)
  {
    x = r * x * (1 - x);
  }
  return x;
}

//Lyapunov exponent of the logistic map: below 0 order, above 0 chaos
inline double Lyapunov(double r){
  double x = 0.3;
  double sum = 0;

  for (int k = 0; k < 300; ++k)
  {
    x = r * x * (1 - x);
  }
  for (int k = 0; k < 1000; ++k)
  {
    x = r * x * (1 - x);
    sum += log(fabs(r * (1 - 2 * x)) + 1e-12);
  }
  return sum / 1000;
}

//sine map x -> r sin(pi x): the same road to chaos as the logistic map
inline double SineMap(double r){
  double x = 0.3;
  int steps = 500 + Phase(r);

  for (int k = 0; k < steps; ++k)
  {
    x = r * sin(M_PI * x);
  }
  return x;
}

//Mandelbrot set on the real line: z -> z^2 + c
inline double Mandelbrot(double c){
  double z = 0;
  int steps = 500 + Phase(c);

  for (int k = 0; k < steps; ++k)
  {
    z = z * z + c;
    if (fabs(z) > 2) return NAN;
  }
  return z;
}

//
//fractals and noise
//

//Takagi-Landsberg: Blancmange with weight w, sum of w^n Triangle(2^n x)
inline double Takagi(double w, double x){
  double y = 0;
  double a = 1;
  double p = 1;

  for (int n = 0; n < 30; ++n)
  {
    y += a * Triangle(p * x);
    a *= w;
    p *= 2;
  }
  return y;
}

//Minkowski question mark: takes the continued fraction of x to binary
inline double Minkowski(double x){
  double y = 0;
  double sign = 1;
  int total = 0;
  int a = 0;
  double whole = floor(x);

  x -= whole;

  for (int k = 0; k < 40 && x > 1e-12; ++k)
  {
    x = 1 / x;
    a = (int) floor(x);
    x -= a;
    total += a;
    if (total > 60) break;
    y += sign * 2 * pow(2, -total);
    sign = -sign;
  }
  return whole + y;
}

//a random number between 0 and 1 for each integer n, always the same
inline double Hash(double n){
  return Mod(sin(n * 127.1 + 311.7) * 43758.5453, 1);
}

//smooth noise: random values on integers, smoothly joined
inline double Noise(double x){
  double n = floor(x);
  double f = x - n;
  double s = f * f * (3 - 2 * f);

  return Hash(n) * (1 - s) + Hash(n + 1) * s;
}

//mountains: noise on top of noise, each layer twice as fine and half as tall
inline double Terrain(double x){
  double y = 0;
  double a = 1;
  double p = 1;

  for (int k = 0; k < 6; ++k)
  {
    y += a * Noise(p * x + 17 * k);
    a /= 2;
    p *= 2;
  }
  return y;
}

//city: one building per unit, each of a random height
inline double Skyline(double x){
  return floor(Hash(floor(x)) * 8) + 1;
}

//
//shapes
//

//top of the Batman logo
inline double BatmanTop(double x){
  double a = fabs(x);

  if (a > 7)    return NAN;
  if (a >= 3)   return 3 * sqrt(1 - (x / 7) * (x / 7));
  if (a >= 1)   return 6 * sqrt(10) / 7 + (1.5 - 0.5 * a) - 6 * sqrt(10) / 14 * sqrt(4 - (a - 1) * (a - 1));
  if (a >= 0.75) return 9 - 8 * a;
  if (a >= 0.5) return 3 * a + 0.75;
  return 2.25;
}

//bottom of the Batman logo
inline double BatmanBottom(double x){
  double a = fabs(x);

  if (a > 7)  return NAN;
  if (a >= 4) return -3 * sqrt(1 - (x / 7) * (x / 7));
  return a / 2 - (3 * sqrt(33) - 7) / 112 * x * x - 3 + sqrt(1 - pow(fabs(a - 2) - 1, 2));
}

//heartbeat: the P wave, the QRS spike and the T wave, once per unit
inline double Ecg(double x){
  double p = Mod(x, 1);

  return 0.12 * exp(-pow((p - 0.20) / 0.035, 2))
       - 0.10 * exp(-pow((p - 0.37) / 0.010, 2))
       + 1.00 * exp(-pow((p - 0.40) / 0.012, 2))
       - 0.25 * exp(-pow((p - 0.43) / 0.012, 2))
       + 0.30 * exp(-pow((p - 0.65) / 0.050, 2));
}

#endif //_MATH_PLO_TEXT_ARSENAL_HPP_
