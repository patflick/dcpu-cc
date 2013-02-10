libdcpu-cc
=======

An ANSI-C (C89) compiler for the DCPU16.
Originally created as replacement for the DCPUToolchain C compiler, this is now a stand-alone
compiler library, that can be used in any projects.

To build you simply need a C++ compiler, Bison, Flex and CMake.

## Build Instructions

### Linux

For Ubuntu (and Debian based systems) download these packages:

```
sudo apt-get install bison flex cmake build-essential
```

Then building is as simple as:

```
mkdir build
cd build
cmake ../
make
```

### Windows

TODO: somebody with windows needs to insert what packages/programs are needed.

Building should be possible with:
```
cmake -G "Visual Studio 10"
make
```
