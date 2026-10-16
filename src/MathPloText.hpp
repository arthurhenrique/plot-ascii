#ifndef _MATH_PLO_TEXT_HPP_
#define _MATH_PLO_TEXT_HPP_

#define MAX_DEFAULT 10

#include <stdio.h>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

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

  //Same graph as PlotGraph, drawing x_point from left to right
  void AnimateGraph(std::function<double (double,double)> func, double __y, int delay_ms = 150);

  //Add a function y = func(x) to be plotted with token
  void AddCurve(std::function<double (double)> func, char token = '#');

  //Remove every curve added
  void ClearCurves();

  //Plot every curve added
  void PlotCurves();

  //Plot every curve added, column by column, like a pen drawing it
  void AnimateCurves(int delay_ms = 30);

  //Init a matrix 
  void SetMatrix(int length = MAX_DEFAULT);    

  //Window of the curves: x and y range, width and height in chars
  void SetWindow(double x_min, double x_max, double y_min, double y_max,
                 int width = 57, int height = 30);

  //Find y range that fits every curve added
  void FitWindow();

  //Configuration
  void SetConfig(char token_xy = '#', char token_x = '-', char token_y = '|',  char token_default = '`');


private:
  //Draw axes on grid
  void ClearGrid();

  //Draw every curve on one column of grid, returns row of first curve
  int DrawColumn(int column);

  //Print grid on screen
  void PrintGrid();

  //Atributes
  int length_max_;
  int length_min_;
  Point* point_;

  //Curves
  std::vector<Curve> curves_;
  std::vector<std::string> grid_;
  double x_min_;
  double x_max_;
  double y_min_;
  double y_max_;
  int width_;
  int height_;

  //Configurations
  char token_xy_;
  char token_y_;
  char token_x_;
  char token_default_;

};

#endif //_MATH_PLO_TEXT_HPP_
