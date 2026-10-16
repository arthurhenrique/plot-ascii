#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "MathPloText.hpp"
#include "MathPloTextParser.hpp"

using namespace std;


//x^2, Matharium and SinCosh, plotted or animated
void Samples(MathPloText *math, bool animate)
{
  math->SetMatrix();

  if (animate) math->AnimateGraph(Pow, 2);
  else         math->PlotGraph(Pow, 2);

  cout << endl
       << "y = (1 - 2*floor(2*(x mod 1))) * |sin(pi*x/4)| * x + |x| - 10" << endl
       << endl;

  math->AddCurve(Matharium);
  math->SetWindow(-20, 8, -11, 27, 57, 39);

  if (animate) math->AnimateCurves();
  else         math->PlotCurves();

  cout << endl
       << "y = sin(6.5x)^2 / cosh(x/2.6)" << endl
       << endl;

  math->ClearCurves();
  math->AddCurve(SinCosh);
  math->SetWindow(-4, 4, -0.1, 1.05, 57, 18);

  if (animate) math->AnimateCurves();
  else         math->PlotCurves();
}

void Help()
{
  cout << "usage: ./MathPloText [-a] [-x MIN:MAX] [-y MIN:MAX] [-s WIDTHxHEIGHT] \"f(x)\" ..." << endl
       << endl
       << "  -a               animate, drawing x from left to right" << endl
       << "  -x MIN:MAX       x range (default -10:10)" << endl
       << "  -y MIN:MAX       y range (default fits the curves)" << endl
       << "  -s WIDTHxHEIGHT  size in chars (default 57x30)" << endl
       << endl
       << "  numbers, x, pi, e, + - * / ^ mod, |abs|, 2x" << endl
       << "  sin cos tan asin acos atan sinh cosh tanh exp ln log sqrt abs floor ceil round" << endl
       << "  D(f) derivative, I(f) integral from 0 to x, I(f,a) from a to x" << endl
       << endl
       << "  ./MathPloText -x -6.3:6.3 \"sin(x)\" \"D(sin(x))\" \"I(sin(x))\"" << endl
       << "  ./MathPloText -a             animate the samples (x^2, Matharium, SinCosh)" << endl
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
      math->AddCurve([parser](double x){ return parser->Eval(x); }, token);
      cout << "  " << token << "  y = " << argv[i] << endl;
      ++curves;
    }
  }

  //no expression: samples
  if (curves == 0)
  {
    Samples(math, animate);
    return 0;
  }

  if (x_min >= x_max || y_min > y_max || width < 2 || height < 2)
  {
    cout << "bad -x, -y or -s" << endl;
    return 1;
  }

  math->SetWindow(x_min, x_max, y_min, y_max, width, height);
  if (fit) math->FitWindow();

  if (animate) math->AnimateCurves();
  else         math->PlotCurves();

  return 0;
}
