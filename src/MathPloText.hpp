#ifndef _MATH_PLO_TEXT_HPP_
#define _MATH_PLO_TEXT_HPP_

#define MAX_DEFAULT 10

#include <stdio.h>
#include <cmath>
#include <functional>

#include "MathPloTextFunction.hpp"
#include "MathPloTextStruct.hpp"

class MathPloText
{
public:
  //Costructor
  MathPloText();

  //Destructor
  ~MathPloText();

  //Parameter and call function by address value 
  void PlotGraph(std::function<double (double,double)> func, double __y);

  //Init a matrix 
  void SetMatrix(int length = MAX_DEFAULT);    

  //Configuration
  void SetConfig(char token_xy = '#', char token_x = '-', char token_y = '|',  char token_default = '`');


private:
  //Atributes
  int length_max_;
  int length_min_;
  Point* point_;

  //Configurations
  char token_xy_;
  char token_y_;
  char token_x_;
  char token_default_;

};

#endif //_MATH_PLO_TEXT_HPP_
