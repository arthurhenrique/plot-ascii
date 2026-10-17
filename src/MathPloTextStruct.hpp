#ifndef _MATH_PLO_TEXT_STRUCT_H_
#define _MATH_PLO_TEXT_STRUCT_H_

#include <functional>

typedef struct
{
  int x;
  int y;
}Point;

typedef struct
{
  std::function<double (double,double)> func; //y = func(x, t)
  char token;
}Curve;

#endif //_MATH_PLO_TEXT_STRUCT_H_
