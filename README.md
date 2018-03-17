# Fourier Depth of Field

My own implementation of the adaptive sampling method for defocus blur by
[Cyril Soler et al, Fourier Depth of Field, 2009](https://github.com/Liby99/FourierDepthOfField/blob/master/docs/paper/a18-soler.pdf).
This project itself contains a self-written path tracer and based on that we
added Fourier analysis to do adaptive sampling. Finally we are able to produce
some very interesting results.

![header]

## Reports

- [Milestone Report](https://github.com/Liby99/FourierDepthOfField/blob/master/docs/milestone.md)
- [Final Report](https://github.com/Liby99/FourierDepthOfField/blob/master/docs/final.md)

## Installation

First clone the repo recursively

``` bash
$ git clone --recursive https://github.com/Liby99/FourierDepthOfField.git
```

Then use CMake and Make to build the program

``` bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Finally you can go to the test folder and run any test you want

``` bash
$ cd test
$ ./cubes_fdof
```

## File Structures

```
docs/ <- Contains Documents
include/ <- GLM, Hierarchical Importance Sampling Libraries
res/ <- Resources: Models, Textures
script/ <- Other scripts for building and compilation
src/ <- Source code
  - extern/ <- Header Files
  - intern/ <- CPP Files
test/ <- Test code, will be compiled to test/ folder and include main() for each file
```

## Disclaimer

We have also included the
[Victor et al, Hierarchical Importance Sampling, 2004](https://github.com/Liby99/FourierDepthOfField/blob/master/docs/paper/importancesampling.pdf)
paper and its source code (include/quasi_sampler), though we modified a little
bit to adapt it into our own structures.

[header]: docs/res/final/header.png
