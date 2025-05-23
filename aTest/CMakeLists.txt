cmake_minimum_required(VERSION 3.14)
#project(Template VERSION 0.1.0)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suppress developer warnings
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1)

include(FetchContent)


FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(aTest Test01.cpp Test02.cpp)

target_link_libraries(
  aTest LINK_PUBLIC gtest_main
)
target_link_libraries(
  aTest LINK_PUBLIC libController
)

include(GoogleTest)
gtest_add_tests(aTest "" Test01.cpp Test02.cpp)
#gtest_discover_tests(aTest)

#target_include_directories (InvTest PUBLIC "C://git//googletest//googletest//include")

target_include_directories (aTest PUBLIC "..\\build\\_deps\\googletest-src\\googletest\\include\\gtest")
target_include_directories (aTest PUBLIC "..\\build\\_deps\\googletest-src\\googletest\\include")
