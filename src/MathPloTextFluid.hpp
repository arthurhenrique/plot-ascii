#ifndef _MATH_PLO_TEXT_FLUID_HPP_
#define _MATH_PLO_TEXT_FLUID_HPP_

/*
Functions of x and time t: exact solutions of the Navier-Stokes equations
and of other famous equations of physics. Animate them with -t.
*/

#include <cmath>
#include <complex>


//Lamb-Oseen vortex: a whirlpool that spreads out as viscosity eats it
//velocity across the vortex, v = (1 - e^(-r^2 / 4 nu t)) / r
inline double LambOseen(double x, double t){
  double nu = 0.2;
  double r  = fabs(x);

  if (r == 0) return 0;

  return (1 - exp(-r * r / (4 * nu * (t + 0.05)))) / x;
}

//Stokes' first problem: a plate under the fluid starts moving at once,
//x is the height above the plate, u = erfc(x / 2 sqrt(nu t))
inline double Stokes1(double x, double t){
  if (x < 0) return NAN;
  if (t <= 0) return x == 0 ? 1 : 0;

  return erfc(x / (2 * sqrt(t)));
}

//Stokes' second problem: a plate going back and forth under the fluid,
//u = e^(-x) cos(t - x)
inline double Stokes2(double x, double t){
  if (x < 0) return NAN;

  return exp(-x) * cos(t - x);
}

//flow in a channel from -1 to 1 starting from rest, pushed by a constant
//pressure, until it becomes the parabola 1 - x^2 (Poiseuille)
inline double Poiseuille(double x, double t){
  double u = 1 - x * x;

  if (fabs(x) > 1) return NAN;

  for (int k = 0; k < 30; ++k)
  {
    int n = 2 * k + 1;
    double sign = k % 2 == 0 ? 1 : -1;
    u -= sign * 32 / (pow(n * M_PI, 3)) * cos(n * M_PI * x / 2) * exp(-n * n * M_PI * M_PI * t / 4);
  }
  return u;
}

//Burgers: the 1D Navier-Stokes. A sine wave steepens into a shock at t = 1,
//viscosity nu keeps it from breaking. Exact solution by the Cole-Hopf transform.
inline double Burgers(double x, double t){
  double nu    = 0.05;
  int    n     = 1001;
  double width = 0;
  double top   = -INFINITY;
  double up    = 0;
  double down  = 0;
  double y     = 0;
  double e     = 0;
  double w     = 0;

  if (t <= 0) return -sin(x);

  width = t + 12 * sqrt(2 * nu * t) + 0.5;

  //biggest exponent first, so exp() never overflows
  for (int i = 0; i < n; ++i)
  {
    y = x - width + 2 * width * i / (n - 1);
    e = (1 - cos(y)) / (2 * nu) - (x - y) * (x - y) / (4 * nu * t);
    if (e > top) top = e;
  }

  for (int i = 0; i < n; ++i)
  {
    y = x - width + 2 * width * i / (n - 1);
    e = (1 - cos(y)) / (2 * nu) - (x - y) * (x - y) / (4 * nu * t);
    w = exp(e - top);
    up   += (x - y) / t * w;
    down += w;
  }
  return up / down;
}

//heat equation: a block of heat spreading out, exact solution with erf
inline double Heat(double x, double t){
  if (t <= 0) return fabs(x) < 1 ? 1 : 0;

  return (erf((1 - x) / (2 * sqrt(t))) + erf((1 + x) / (2 * sqrt(t)))) / 2;
}

//wave equation: a plucked bump splits into two going opposite ways (d'Alembert)
inline double Pluck(double x, double t){
  return (exp(-4 * (x - t) * (x - t)) + exp(-4 * (x + t) * (x + t))) / 2;
}

//KdV equation: two solitons, the tall fast one passes through the small one
//and both come out the same. u = 2 (ln F)''
inline double SolitonF(double x, double t){
  double k1 = 2;
  double k2 = 1;
  double e1 = k1 * x - k1 * k1 * k1 * t + 24;
  double e2 = k2 * x - k2 * k2 * k2 * t + 4;
  double a  = pow((k1 - k2) / (k1 + k2), 2);

  return log(1 + exp(e1) + exp(e2) + a * exp(e1 + e2));
}

inline double Soliton(double x, double t){
  double h = 1e-3;
  return 2 * (SolitonF(x + h, t) - 2 * SolitonF(x, t) + SolitonF(x - h, t)) / (h * h);
}

//Schrodinger equation: a free electron, a wave packet moving and spreading
inline std::complex<double> Psi(double x, double t){
  std::complex<double> i(0, 1);
  double k = 3;
  std::complex<double> s = 1.0 + i * t / 2.0;

  return pow(2 * M_PI, -0.25) / sqrt(s)
         * exp(-(x - k * t) * (x - k * t) / (4.0 * s) + i * k * x - i * k * k * t / 2.0);
}

//real part of the wave
inline double Packet(double x, double t){
  return Psi(x, t).real();
}

//where the electron can be, |psi|^2
inline double PacketDensity(double x, double t){
  return std::norm(Psi(x, t));
}

#endif //_MATH_PLO_TEXT_FLUID_HPP_
