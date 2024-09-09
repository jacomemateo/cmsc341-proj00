cmake_minimum_required(VERSION 3.27)
project(project_0)

set(CMAKE_CXX_STANDARD 17)

add_executable(project_0 src/driver.cpp src/solitaire.cpp)

add_executable(mytest src/mytest.cpp src/solitaire.cpp)