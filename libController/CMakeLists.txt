cmake_minimum_required(VERSION 3.14)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#-fprofile-arcs -ftest-coverage

add_library(libController STATIC Controller.cpp HomeHeatModel.cpp State.cpp IdleState.cpp CoolingState.cpp HeatingState.cpp SetPointState.cpp DiurnalSurfaceModel.cpp) 

# Make sure the compiler can find include files for our  library
# when other libraries or executables link to the library
target_include_directories (libController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})