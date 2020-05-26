## calc
This is a simple calc in lex(flex) and Yacc(bison).

## Clone

```
git clone https://github.com/wesllhey/calc.git
```

## Installing dependencies

* gcc/clang
* flex(win_flex)
* bison(win_bison)

## How to run

Linux:
```
$ make
$ ./calc
```

## Examples
```
> 1 + 1
> 2
> 3 - 1
> 2
> 2 + 3 + 4 + 0
> 9
> 2 * (5 + 3)
> 16
> 5+
syntax error
> number1 = 9
> number2 = 11
> number1
> 9
> number2
> 11
> number1 + number2
> 20
> sqrt(number1)
> 3
> log2(16)
> 4
```

If you find some errors, plaese open an issue!
