cmake_minimum_required(VERSION 3.17)

project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lab4 main.cpp)

target_sources(lab4 PRIVATE MyStack.h)

target_include_directories(lab4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})