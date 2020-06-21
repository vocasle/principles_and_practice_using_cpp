# Solutions for "Principles and Practice Using C++"

This repository contains my implementation of solutions for problems listed in the book.

### Prerequisites

1. C++ compiler that supports C++17.
2. CMake 3.15+.
3. To compile exercises from chapter 12-16 FLTK 1.3 is required.

#### FLTK 1.3 Installation

1. Clone FLTK from their [GitHub repo](https://github.com/fltk/fltk).
2. Checkout branch `branch-1.3`.
3. Follow instructions for your OS from [README.CMake.txt](https://github.com/fltk/fltk/blob/master/README.CMake.txt) to build the library.
4. Set `FLTK_DIR` variable, i.e. replace `$ENV{FLTK_HOME}` in
 `set(FLTK_DIR "$ENV{FLTK_HOME}")` 
in top `CMakeLists.txt` to directory that contains
`FLTKConfig.cmake`, 
`FLTK-Targets.cmake`, `FLTK-Targets-release.cmake`,
`UseFLTK.cmake`.

### Table of Content

1. Part I: The Basics
   - [X] Chapter 4
   - [X] Chapter 5
   - [X] Chapter 6
   - [X] Chapter 7
   - [X] Chapter 8
   - [X] Chapter 9
   - [X] Chapter 10
2. Part II: Input and Output
   - [X] Chapter 11
   - [X] Chapter 12
   - [X] Chapter 13
   - [X] Chapter 14
   - [X] Chapter 15
   - [X] Chapter 16
