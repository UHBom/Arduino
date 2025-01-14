
[![Arduino CI](https://github.com/RobTillaart/Distancetable/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/DistanceTable/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/DistanceTable/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/DistanceTable/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/DistanceTable/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/Distancetable/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/Distancetable.svg?maxAge=3600)](https://github.com/RobTillaart/Distancetable/releases)


# Distancetable

Arduino library to store a symmetrical distance table in less memory.


## Description

The DistanceTable library is a class that stores a symmetrical distance table 
which is typically N x N entries in less memory space. 
It uses (N x (N-1))/2 ("in a triangle") as an euclidean distance table is 
symmetrical around its main diagonal. 
Furthermore as the main diagonal are all zero it does not need to be stored either.

An ATMEL328 (Arduino) can store a 30 x 30 matrix = 900 floats in 1740 bytes, 
where it typically would take 900 x 4 = 3600 bytes. 

Within the 2K RAM of an Arduino one could store normally a 21 x 21 matrix (1764 bytes).


## Interface

- **DistanceTable(uint8_t size, float value = 0.0)** Constructor, allocates memory and 
sets initial value to all elements.
- **~DistanceTable();** Destructor, frees memory
- **void clear()** sets all entries to 0.0.
- **void setAll(float value)** sets all entries to value;
- **void set(uint8_t x, uint8_t y, float value )** sets a value for (x,y) and automatically for (y, x)
- **float get(uint8_t x, uint8_t y)** gets a value from (x,y). If x == y it will return 0.
- **float minimum(uint8_t &x, uint8_t &y)** Returns minimum and first occurrence in x and y. 
It does skip x == y pairs as these are 0.
- **float maximum(uint8_t &x, uint8_t &y)** Returns maximum and first occurrence in x and y. 
It does skip x == y pairs as these are 0.


### count

- **uint16_t count(value, epsilon)** counts the number of occurrences of value. 
As we are comparing floats the epsilon can set a margin for 'almost equal'.
- **uint16_t countAbove(float value)** counts the number of occurrences larger than value.
- **uint16_t countBelow(float value)** counts the number of occurrences smaller than value.

Note 1: these 3 numbers do not always add up exactly as **count()** uses an epsilon where the
other two do not. 
Note 2: the functions do not count the x == y diagonal. Behaviour might change in the future.


### Invert (experimental)

- **void setInvert(bool invert = false)** Set the invert flag. 
- **bool getInvert()** returns the current value of the invert flag.

Normally the table is value symmetrical around the y == x diagonal.
With the invert flag, all values are inverted ==> **get(x, y) == -get(y, x)**.
This allows other uses for the table for only a few bytes of RAM.
The table becomes a magnitude symmetrical distance table.

The performance of the distance table is affected by the invert flag as most
functions need to test it. 
In practice this means slower, especially when the flag is set to true.

Some application thoughts:
- difference in height
- energy levels e.g. transitions of electrons, other physics
- transactions between players of a game
- hold a 2D colour space

Note: this function is not tested extensively.


### Debug

- **void dump(Print \* stream = &Serial)** dumps complete distance table, default to Serial. Note in previous releases it dumped only a "triangle".
- **uint8_t dimension()** dimension of the table == parameter in constructor.
- **uint16_t elements()** amount of elements allocated.
- **uint16_t memoryUsed()** amount of memory used. Typical 4 x elements().


## Operational

See examples.


## Future

- improve documentation
- **clear()** could set all to NAN? is that better as it indicates unknown?  
  - setAll() let the user decide.
- add examples
  - Note: table can be used for other symmetrical 2D tables. 
  - And therefore include negative values
  - pascal tree in matrix?
- improve unit tests 
- sum of all distances?
  - sum, average, ... 
- investigate behaviour of **count()** functions a bit more.
  - include diagonal?


#### derived or related classes 

- int64_t int32_t int16_t int8_t  + unsigned variants? (8 variations? invert flag)
  - Template class?
- should the "non-inverted" distance table be a derived (performant) class?
- diagonal not zero class, 
  - uses a more bytes but allows also extra functionality while staying symmetrical.



#### won't 

- Hamilton paths? 
- very sparse matrix?
  - array of struct (x, y, value);
  - ==> another class

