
cmake_minimum_required(VERSION 3.23)

project(lab5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lab5 main.cpp)

target_sources(lab5 PRIVATE MyVector.h MySet.h)

target_include_directories(lab5 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})