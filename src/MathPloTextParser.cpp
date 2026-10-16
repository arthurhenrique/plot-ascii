#include <cctype>
#include <cmath>
#include <cstdlib>

#include "MathPloTextParser.hpp"
#include "MathPloTextFunction.hpp"


MathPloTextParser::MathPloTextParser(std::string expr)
{
  expr_     = expr;
  position_ = 0;
  pos_      = 0;
  abs_      = 0;
  x_        = 0;
}

double MathPloTextParser::Eval(double x)
{
  x_     = x;
  pos_   = 0;
  abs_   = 0;
  error_ = "";

  double y = Expression();

  Spaces();
  if (pos_ < (int) expr_.size()) Fail(std::string("unexpected '") + expr_[pos_] + "'");
  if (!error_.empty()) return NAN;

  return y;
}

bool MathPloTextParser::Check()
{
  Eval(0);
  return error_.empty();
}

std::string MathPloTextParser::Error()
{
  return error_;
}

int MathPloTextParser::Position()
{
  return position_;
}

// expression := term (+ term | - term)*
double MathPloTextParser::Expression()
{
  double y = Term();

  while (error_.empty())
  {
    if      (Accept('+')) y += Term();
    else if (Accept('-')) y -= Term();
    else break;
  }
  return y;
}

// term := unary (* unary | / unary | mod unary | unary)*
double MathPloTextParser::Term()
{
  double y = Unary();

  while (error_.empty())
  {
    if      (Accept('*')) y *= Unary();
    else if (Accept('/')) y /= Unary();
    else if (AcceptMod()) y = Mod(y, Unary());
    else if (Factor())    y *= Power();
    else break;
  }
  return y;
}

// unary := -unary | +unary | power
double MathPloTextParser::Unary()
{
  if (Accept('-')) return -Unary();
  if (Accept('+')) return Unary();
  return Power();
}

// power := primary (^ unary)?
double MathPloTextParser::Power()
{
  double y = Primary();

  if (Accept('^')) y = pow(y, Unary());
  return y;
}

// primary := number | x | pi | e | (expression) | |expression| | name(...)
double MathPloTextParser::Primary()
{
  Spaces();

  if (pos_ >= (int) expr_.size())
  {
    Fail("expression ends too early");
    return 0;
  }

  char c = expr_[pos_];

  //number
  if (isdigit(c) || c == '.')
  {
    char* end = 0;
    double y = strtod(expr_.c_str() + pos_, &end);
    pos_ = end - expr_.c_str();
    return y;
  }

  //(expression)
  if (Accept('('))
  {
    double y = Expression();
    if (!Accept(')')) Fail("expected ')'");
    return y;
  }

  //|expression|
  if (Accept('|'))
  {
    ++abs_;
    double y = Expression();
    --abs_;
    if (!Accept('|')) Fail("expected '|'");
    return fabs(y);
  }

  //name
  if (isalpha(c))
  {
    int start = pos_;
    while (pos_ < (int) expr_.size() && isalnum(expr_[pos_])) ++pos_;
    std::string name = expr_.substr(start, pos_ - start);

    if (name == "x")  return x_;
    if (name == "pi") return M_PI;
    if (name == "e")  return M_E;

    if (Accept('(')) return Function(name);

    pos_ = start;
    Fail("unknown name '" + name + "'");
    return 0;
  }

  Fail(std::string("unexpected '") + c + "'");
  return 0;
}

// name(expression) or name(expression, expression)
double MathPloTextParser::Function(std::string name)
{
  int start = pos_;
  double y = Expression();
  int end = pos_;

  //D(f) and I(f) calculate f again on other values of x
  if (name == "D" || name == "I")
  {
    MathPloTextParser inner(expr_.substr(start, end - start));
    std::function<double (double)> f = [&inner](double x){ return inner.Eval(x); };

    if (name == "D")
    {
      y = Derivative(f, x_);
    }
    else
    {
      double from = 0;
      if (Accept(',')) from = Expression();
      y = Integral(f, from, x_);
    }
  }
  else if (name == "sin")   y = sin(y);
  else if (name == "cos")   y = cos(y);
  else if (name == "tan")   y = tan(y);
  else if (name == "asin")  y = asin(y);
  else if (name == "acos")  y = acos(y);
  else if (name == "atan")  y = atan(y);
  else if (name == "sinh")  y = sinh(y);
  else if (name == "cosh")  y = cosh(y);
  else if (name == "tanh")  y = tanh(y);
  else if (name == "exp")   y = exp(y);
  else if (name == "ln")    y = log(y);
  else if (name == "log")   y = log10(y);
  else if (name == "sqrt")  y = sqrt(y);
  else if (name == "abs")   y = fabs(y);
  else if (name == "floor") y = floor(y);
  else if (name == "ceil")  y = ceil(y);
  else if (name == "round") y = round(y);
  else
  {
    pos_ = start - 1 - (int) name.size();
    Fail("unknown function '" + name + "'");
    return 0;
  }

  if (!Accept(')')) Fail("expected ')'");
  return y;
}

void MathPloTextParser::Spaces()
{
  while (pos_ < (int) expr_.size() && isspace(expr_[pos_])) ++pos_;
}

bool MathPloTextParser::Accept(char c)
{
  Spaces();
  if (pos_ < (int) expr_.size() && expr_[pos_] == c)
  {
    ++pos_;
    return true;
  }
  return false;
}

bool MathPloTextParser::AcceptMod()
{
  Spaces();
  if (expr_.compare(pos_, 3, "mod") == 0)
  {
    pos_ += 3;
    return true;
  }
  return false;
}

// something right after a factor means multiply: 2x, 3(x+1), |x|x
// a '|' only opens a new |abs| when we are not inside one
bool MathPloTextParser::Factor()
{
  Spaces();
  if (pos_ >= (int) expr_.size()) return false;

  char c = expr_[pos_];
  if (c == '|') return abs_ == 0;
  return isalnum(c) || c == '.' || c == '(';
}

void MathPloTextParser::Fail(std::string error)
{
  if (!error_.empty()) return;
  error_    = error;
  position_ = pos_;
}
