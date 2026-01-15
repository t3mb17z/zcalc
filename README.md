# ZCalc
## A simple calculator for the command line

### Overview
This is a really simple `infix -> postfix` calculator
for your terminal.

### Features
* **Multiple operator** - like `+`, `-`, `*`, `/`, and `^` (power)
* **Nested parenthesis** - `(1+(2-5^(2+5)))`
* **Robust** - process +90k tokens in less than 100ms
* **High precision** - up to 14 decimals
* **Extense range** - Extended to long range

### Requirements
* `make` (for building)
* A **C** compiler (GCC/Clang)

## Building
Compile and run with:
```sh
make all run
```

## Usage
```sh
./zcalc "(3+4)^4"
```
