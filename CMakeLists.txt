cmake_minimum_required(VERSION 3.14)

project(State_Controller VERSION 0.1.0 LANGUAGES C CXX)

#add_compile_options("$<$<COMPILE_LANGUAGE:CXX>: -DGLIBCXX_ASSERTIONS>")

# -Ofast;-DNDEBUG;-std=c++20;-march=native;-fpic;-ftree-vectorize;
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
set(CMAKE_CXX_STANDARD 17)
find_package(Qt6 COMPONENTS Charts REQUIRED)

add_subdirectory(libController)
add_subdirectory(aTest)
add_subdirectory(theApp)


#add_executable(cpptest cpptest.cpp)

