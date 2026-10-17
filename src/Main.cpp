#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "MathPloText.hpp"
#include "MathPloTextParser.hpp"

using namespace std;


//x^2, plotted or animated
void Sample(MathPloText *math, bool animate)
{
  math->SetMatrix();

  if (animate) math->AnimateGraph(Pow, 2);
  else         math->PlotGraph(Pow, 2);
}

void Help()
{
  cout << "usage: ./MathPloText [-a | -t MAX] [-d MS] [-x MIN:MAX] [-y MIN:MAX] [-s WIDTHxHEIGHT] \"f(x)\" ..." << endl
       << endl
       << "  -a               animate, drawing x from left to right" << endl
       << "  -t MAX           animate time t from 0 to MAX" << endl
       << "  -d MS            milliseconds between frames (default 30 for -a, 60 for -t)" << endl
       << "  -x MIN:MAX       x range (default -10:10)" << endl
       << "  -y MIN:MAX       y range (default fits the curves)" << endl
       << "  -s WIDTHxHEIGHT  size in chars (default 57x30)" << endl
       << endl
       << "  numbers, x, t, pi, e, + - * / ^ mod, |abs|, 2x" << endl
       << "  sin cos tan exp ln sqrt floor ... and every function in the README" << endl
       << "  D(f) derivative, I(f) integral from 0 to x, I(f,a) from a to x" << endl
       << endl
       << "  ./MathPloText -x -6.3:6.3 \"sin(x)\" \"D(sin(x))\" \"I(sin(x))\"" << endl
       << "  ./MathPloText -a             animate x^2" << endl
       << "  ./MathPloText -t 3 -x -3.2:3.2 \"burgers(x, t)\"" << endl
       << "  ./MathPloText -a -x -20:8 \"(1 - 2*floor(2*(x mod 1))) * |sin(pi*x/4)| * x + |x| - 10\"" << endl;
}

int main(int argc, char *argv[])
{
  MathPloText *math = new MathPloText();

  math->SetConfig();

  double x_min   = -10, x_max = 10;
  double y_min   = 0,   y_max = 0;
  int    width   = 57,  height = 30;
  bool   animate = false;
  bool   fit     = true;
  double t_max   = 0;
  int    delay   = -1;

  char tokens[] = "#*+o@%&=";
  int  curves   = 0;

  for (int i = 1; i < argc; ++i)
  {
    if (strcmp(argv[i], "-h") == 0)
    {
      Help();
      return 0;
    }
    else if (strcmp(argv[i], "-a") == 0)
    {
      animate = true;
    }
    else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
    {
      sscanf(argv[++i], "%lf", &t_max);
    }
    else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc)
    {
      sscanf(argv[++i], "%d", &delay);
    }
    else if (strcmp(argv[i], "-x") == 0 && i + 1 < argc)
    {
      sscanf(argv[++i], "%lf:%lf", &x_min, &x_max);
    }
    else if (strcmp(argv[i], "-y") == 0 && i + 1 < argc)
    {
      sscanf(argv[++i], "%lf:%lf", &y_min, &y_max);
      fit = false;
    }
    else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc)
    {
      sscanf(argv[++i], "%dx%d", &width, &height);
    }
    else
    {
      MathPloTextParser *parser = new MathPloTextParser(argv[i]);

      if (!parser->Check())
      {
        cout << "error: " << parser->Error() << endl
             << "  " << argv[i] << endl
             << "  " << string(parser->Position(), ' ') << "^" << endl;
        return 1;
      }

      char token = tokens[curves % 8];
      math->AddWave([parser](double x, double t){ return parser->Eval(x, t); }, token);
      cout << "  " << token << "  y = " << argv[i] << endl;
      ++curves;
    }
  }

  //no expression: x^2
  if (curves == 0)
  {
    Sample(math, animate);
    return 0;
  }

  if (x_min >= x_max || y_min > y_max || width < 2 || height < 2 || t_max < 0)
  {
    cout << "bad -x, -y or -s" << endl;
    return 1;
  }

  math->SetWindow(x_min, x_max, y_min, y_max, width, height);
  if (fit) math->FitWindow(t_max);

  if (t_max > 0)    math->AnimateTime(t_max, 60, delay < 0 ? 60 : delay);
  else if (animate) math->AnimateCurves(delay < 0 ? 30 : delay);
  else              math->PlotCurves();

  return 0;
}
