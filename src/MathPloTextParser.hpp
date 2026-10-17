#ifndef _MATH_PLO_TEXT_PARSER_HPP_
#define _MATH_PLO_TEXT_PARSER_HPP_

#include <string>

/*
Read a function of x written as text and calculate it.

  numbers 2 3.5   constants pi e   variable x
  + - * / ^ mod   |abs|   2x 3(x+1) |x|x (implicit *)
  sin cos tan asin acos atan sinh cosh tanh exp ln log sqrt abs floor ceil round
  triangle blancmange expsaw expmod weierstrass riemann cantor
  heart square sinc bessel gamma matharium sincosh
  D(f)     derivative of f
  I(f)     integral of f from 0 to x
  I(f,a)   integral of f from a to x
*/
class MathPloTextParser
{
public:
  //Costructor
  MathPloTextParser(std::string expr);

  //Value of the expression at x
  double Eval(double x);

  //True if the expression can be read; if not, see Error() and Position()
  bool Check();

  std::string Error();
  int Position();

private:
  double Expression();
  double Term();
  double Unary();
  double Power();
  double Primary();
  double Function(std::string name);

  void Spaces();
  bool Accept(char c);
  bool AcceptMod();
  bool Factor();
  void Fail(std::string error);

  //Atributes
  std::string expr_;
  std::string error_;
  int position_;
  int pos_;
  int abs_;
  double x_;
};

#endif //_MATH_PLO_TEXT_PARSER_HPP_
