#include <iostream>

#include "MathPloText.hpp"


using namespace std;


MathPloText::MathPloText()
{
  length_max_ = 0;
  length_min_ = 0;
  point_      = 0;
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
  point_ = new Point[length * length];

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
