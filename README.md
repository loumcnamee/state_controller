# State Controller Example
A C++ project thar implements the state pattern to control an HVAC plant for a house.
The state pattern impplemnted here uses modern C++ (17) feaures to reduce single responsibility and Open closed principle violations of the original pattern. 
Inspired by https://vishalchovatiya.com/posts//state-design-pattern-in-modern-cpp/

This repository contains a C++ application using CMake for the build system.
It includes support to build a static library containing business logic classes, a google test project that test the library and an application that uses the library classes and provides a Qt GUI.

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
* 

## Helpful References
 * https://cmake.org/cmake/help/latest/
 * https://code.visualstudio.com/docs/cpp/cmake-quickstart
 * https://google.github.io/googletest/
 
