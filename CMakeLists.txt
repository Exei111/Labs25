cmake_minimum_required(VERSION 3.23)
project(lab6)

set(CMAKE_CXX_STANDARD 17)

add_library(PolynomialLib STATIC lib/Term.h lib/Polynomial.h lib/MyVector.h lib/PolynomialLib.cpp)

add_executable(lab6 main.cpp)

target_link_libraries(lab6 PRIVATE PolynomialLib)