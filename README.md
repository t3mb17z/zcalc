# ZCalc
## A simple calculator for the command line

### Overview
This is a really simple `infix -> postfix` calculator
for your terminal.

### Features
* **Multiple operators** - `+`, `-`, `*`, `/`, `^` and factorial (`!`)
* **Parenthesis** - Fully support nested expressions
* **Performance** - Process over 90k tokens in under than 100ms
* **Precision** - Floating-point precision up to ~14 decimal digits
* **Extended numeric range** - Based on floating-point types

### Requirements
* `make` (for building)
* A **C** compiler (GCC/Clang)

## Building
### Compile
```sh
# Compile release
make BUILD=release

# Or debug with
make

# Or
make BUILD=debug
```

## Usage
```sh
# Basic operation
./zcalc 3+4

# With parenthesis
./zcalc "(12+8)/(10*2)"

# With nested parenthesis
./zcalc "(3+(4*(2*(2/(4+2))+5)))"

# With factorial and exponentiation
./zcalc "(8+5!)^(2+1/(8*9))"
```
You can use even make to run
```sh
# You can run directly
make run ARGS='here goes your expression'

# For example
make run ARGS='3^4+3!/(3*(5+8))'
```
