# plot-ascii

Cartesian plan plotted with ASCII.

![x^2](./sample/pow.gif)

![Matharium](./sample/matharium.gif)

![SinCosh](./sample/sincosh.gif)

## Run

```sh
cd src && make
./MathPloText        # x^2, Matharium and SinCosh
./MathPloText -a     # animated
```

Any function of x:

```sh
./MathPloText "x^2"
./MathPloText -x -6.3:6.3 "sin(x)" "D(sin(x))" "I(sin(x))"
./MathPloText -a -x -4:4 "sin(6.5x)^2 / cosh(x/2.6)"
```

| option | |
|---|---|
| `-a` | animate |
| `-x MIN:MAX` | x range (default `-10:10`) |
| `-y MIN:MAX` | y range (default fits the curve) |
| `-s WIDTHxHEIGHT` | size (default `57x30`) |

Functions: `+ - * / ^ mod |x| pi e sin cos tan sinh cosh tanh exp ln log sqrt floor ceil round`,
`D(f)` derivative and `I(f)` integral.

## C++

```cpp
MathPloText *math = new MathPloText();

math->SetConfig();
math->SetMatrix();
math->AnimateGraph(Pow, 2);

math->AddCurve(Matharium);
math->SetWindow(-20, 8, -11, 27);
math->AnimateCurves();
```
