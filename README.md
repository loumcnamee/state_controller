# State Controller Example
A C++ project thar implements the state pattern to control an [HVAC](https://en.wikipedia.org/wiki/Heating,_ventilation,_and_air_conditioning)  plant for a house.
The state pattern impplemnted here uses modern C++ (17) feaures to reduce single responsibility and Open closed principle violations of the original pattern. 
Inspired by https://vishalchovatiya.com/posts//state-design-pattern-in-modern-cpp/

This repository contains a C++ application using CMake for the build system.
It includes support to build a static library containing business logic classes, a google test project that test the library and an application that uses the library classes and provides a Qt GUI.

[![codecov](https://codecov.io/gh/loumcnamee/state_controller/graph/badge.svg?token=OIVEPE6RYE)](https://codecov.io/gh/loumcnamee/state_controller)

[![Build status](https://ci.appveyor.com/api/projects/status/yxoqmvvgh04mxvp3?svg=true)](https://ci.appveyor.com/project/loumcnamee/state-controller)

## Organization

### Folder structure
```
├ .vscode           # contains files to support integration with VS Code
├ libController     # contains C++ classes built into the Controller library 
├ aTest             # contains unit tests of classes in teh ocntroller library
├ theApp            # Qt single window application
├ CMakeLists.txt    # main Cmake project file that references CMake projects in aLib, aTest, and theApp folders
```
## Important Files
* CMakeLists.txt    # this is the main CMake project file. Calling it with CMake will configure, build the entire project

## Toolchain

This project was built using a CMake/gcc toolchain in WSL: Ubuntu on Windows
* gcc - gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
* g++ - g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
* CMake - cmake version 3.28.3


## Design
See [Design Documentation](/doc/Design.md) for details on the implementation.

## Dependencies
- Qt Framework
- C++ Standard Library

## Technical Requirements
- C++17 or later
- Qt 5.15 or later
- CMake

## Disclosure
The author (Lou McNamee) used CoPilot to generate some of the code, tests and documentation 


## Helpful References
 * https://cmake.org/cmake/help/latest/
 * https://code.visualstudio.com/docs/cpp/cmake-quickstart
 * https://google.github.io/googletest/
 
