cmake_minimum_required(VERSION 3.8)

# include CTest support
#include(CTest)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set (CMAKE_PREFIX_PATH "C:/msys64/ucrt64/qt5-static/lib/cmake")
set (CMAKE_INCLUDE_PATH "/usr/include/x86_64-linux-gnu/qt6")
set (CMAKE_INCLUDE_PATH "/usr/lib/qt6")
#set (CMAKE_INCLUDE_PATH "~/MetricCode/theApp")
#
# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# a foolproof way to do it yet, so settle for the default error message for now.
#if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
#    message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
#            "environment variable to the install prefix of Qt 5, either on the command line as "
#            "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
#endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Find the QtWidgets library
find_package(Qt6 COMPONENTS REQUIRED Core Gui Widgets Charts)

# Tell CMake to create the helloworld executable
add_executable(theApp theApp.cpp MainWindow.cpp ControlSlider.cpp)
target_compile_features(theApp PRIVATE cxx_std_17)
#target_compile_options(theApp PRIVATE -coverage)
#target_link_options(theApp PRIVATE -coverage)

# Add the Qt5 Widgets for linking
# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# the application
target_link_libraries (theApp  PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Charts libController)

#add_test(NAME coverage COMMAND theApp)