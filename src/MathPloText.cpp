#include <iostream>
#include <unistd.h>

#include "MathPloText.hpp"


using namespace std;


MathPloText::MathPloText()
{
  length_max_ = 0;
  length_min_ = 0;
  point_      = 0;

  SetWindow(-10, 10, -10, 10);
}

MathPloText::~MathPloText()
{
}

/* plot graph using defined function.

*/
void MathPloText::PlotGraph(std::function<double (double,double)> func, double __y)
{
  int count   = 0;
  int y_point = 0;
  int x_point = 0;

  for (y_point = length_max_; y_point > length_min_; --y_point)
  {
    for (x_point = length_min_; x_point < length_max_; ++x_point)
    {
      //(x_point,y_point) will be represent by especial char bellow
      if (x_point == point_[count].x &&
          y_point == Combiner(point_[count].x, __y, func))
      {
        printf("%3c", token_xy_);
      }
      //y_point-axes will be represent by especial char bellow
      else if (x_point == 0)
      {
        printf("%3c", token_y_);
      }
      //x_point-axis will be represent by especial char bellow
      else if ( y_point == 0 )
      {
        printf("%3c",token_x_);
      }
      //complete this graph with this especial char bellow
      else
      {
        printf("%3c", token_default_);
      }
      ++count;
    }
    cout << endl;
    }
}


/* animate graph using defined function: one frame for each x_point,
   only points until x_now are shown, the last one with the pen.

*/
void MathPloText::AnimateGraph(std::function<double (double,double)> func, double __y, int delay_ms)
{
  int count   = 0;
  int y_point = 0;
  int x_point = 0;
  int x_now   = 0;

  for (x_now = length_min_; x_now < length_max_; ++x_now)
  {
    //cursor back to top of the graph, then draw this frame over the last one
    if (x_now > length_min_)
    {
      printf("\033[%dA", length_max_ - length_min_);
    }

    count = 0;

    for (y_point = length_max_; y_point > length_min_; --y_point)
    {
      for (x_point = length_min_; x_point < length_max_; ++x_point)
      {
        //pen on (x_now,y_point)
        if (x_point == x_now &&
            y_point == Combiner(point_[count].x, __y, func))
        {
          printf("%3c", 'O');
        }
        //(x_point,y_point) already drawn will be represent by especial char bellow
        else if (x_point < x_now &&
                 y_point == Combiner(point_[count].x, __y, func))
        {
          printf("%3c", token_xy_);
        }
        //y_point-axes will be represent by especial char bellow
        else if (x_point == 0)
        {
          printf("%3c", token_y_);
        }
        //x_point-axis will be represent by especial char bellow
        else if (y_point == 0)
        {
          printf("%3c", token_x_);
        }
        //complete this graph with this especial char bellow
        else
        {
          printf("%3c", token_default_);
        }
        ++count;
      }
      cout << endl;
    }

    fflush(stdout);
    usleep(delay_ms * 1000);
  }

  //last frame without the pen
  printf("\033[%dA", length_max_ - length_min_);
  PlotGraph(func, __y);
}

/* add a function to be plotted
*/
void MathPloText::AddCurve(std::function<double (double)> func, char token)
{
  Curve curve;
  curve.func  = func;
  curve.token = token;
  curves_.push_back(curve);
}

/* plot every curve added
*/
void MathPloText::PlotCurves()
{
  ClearGrid();

  for (int column = 0; column < width_; ++column)
  {
    DrawColumn(column);
  }

  PrintGrid();
}

/* plot every curve added, one column per frame
*/
void MathPloText::AnimateCurves(int delay_ms)
{
  ClearGrid();

  for (int column = 0; column < width_; ++column)
  {
    int row = DrawColumn(column);

    //pen on the last point drawn
    char under = 0;
    if (row >= 0)
    {
      under = grid_[row][column];
      grid_[row][column] = 'O';
    }

    //cursor back to top of the graph, then draw this frame over the last one
    if (column > 0) printf("\033[%dA", height_);
    PrintGrid();
    fflush(stdout);

    if (row >= 0)
    {
      grid_[row][column] = under;
    }

    usleep(delay_ms * 1000);
  }

  printf("\033[%dA", height_);
  PrintGrid();
}

/* empty grid with x and y axes
*/
void MathPloText::ClearGrid()
{
  grid_.assign(height_, std::string(width_, token_default_));

  double x_step = (x_max_ - x_min_) / (width_ - 1);
  double y_step = (y_max_ - y_min_) / (height_ - 1);

  int x_zero = (int) round(-x_min_ / x_step);
  int y_zero = (int) round(y_max_ / y_step);

  for (int column = 0; column < width_; ++column)
  {
    if (y_zero >= 0 && y_zero < height_) grid_[y_zero][column] = token_x_;
  }

  for (int row = 0; row < height_; ++row)
  {
    if (x_zero >= 0 && x_zero < width_) grid_[row][x_zero] = token_y_;
  }
}

/* one column holds many x values, so curves that jump (like Matharium)
   do not lose their pieces between two chars
*/
int MathPloText::DrawColumn(int column)
{
  int samples   = 20;
  int first_row = -1;

  double x_step = (x_max_ - x_min_) / (width_ - 1);
  double y_step = (y_max_ - y_min_) / (height_ - 1);

  //last curve first, so the first one stays on top
  for (int i = (int) curves_.size() - 1; i >= 0; --i)
  {
    for (int s = 0; s < samples; ++s)
    {
      double x = x_min_ + (column - 0.5 + (s + 0.5) / samples) * x_step;
      double y = curves_[i].func(x);

      int row = (int) round((y_max_ - y) / y_step);

      if (std::isfinite(y) && row >= 0 && row < height_)
      {
        grid_[row][column] = curves_[i].token;
        if (i == 0) first_row = row;
      }
    }
  }

  return first_row;
}

/* same layout as PlotGraph: one char per cell, 3 columns wide
*/
void MathPloText::PrintGrid()
{
  for (int row = 0; row < height_; ++row)
  {
    for (int column = 0; column < width_; ++column)
    {
      printf("%3c", grid_[row][column]);
    }
    cout << endl;
  }
}

void MathPloText::SetWindow(double x_min, double x_max, double y_min, double y_max,
                            int width, int height)
{
  x_min_  = x_min;
  x_max_  = x_max;
  y_min_  = y_min;
  y_max_  = y_max;
  width_  = width;
  height_ = height;
}

/* y range from the lowest to the highest point of the curves
*/
void MathPloText::FitWindow()
{
  int samples = 2000;

  y_min_ = 0;
  y_max_ = 0;

  for (size_t i = 0; i < curves_.size(); ++i)
  {
    for (int s = 0; s <= samples; ++s)
    {
      double y = curves_[i].func(x_min_ + (x_max_ - x_min_) * s / samples);

      if (!std::isfinite(y)) continue;
      if (y < y_min_) y_min_ = y;
      if (y > y_max_) y_max_ = y;
    }
  }

  if (y_max_ - y_min_ < 1) y_max_ = y_min_ + 1;
}

/*
Fill matrix with values
        (x, y)
(-1, 1) (0, 1) (1, 1)
(-1, 0) (0, 0) (1, 0)
(-1,-1) (0,-1) (1,-1)
*/
void MathPloText::SetMatrix(int length)
{
  length_min_ = length * -1;
  length_max_ = length;

  int count   = 0;
  int y_point = 0;
  int x_point = 0;

  //Fill point's struct
  point_ = new Point[(2 * length) * (2 * length)];

  //Fill coordinator x and y based on matrix
  for (y_point = length_max_; y_point > length_min_; --y_point)
  {
    for (x_point = length_min_; x_point < length_max_; ++x_point)
    {
        point_[count].x = x_point;
        point_[count].y = y_point;
        ++count;
    }
  }
}

void MathPloText::SetConfig(char token_xy, char token_x, char token_y, char token_default)
{
  token_xy_      = token_xy;
  token_x_       = token_x;
  token_y_       = token_y;
  token_default_ = token_default;
}
