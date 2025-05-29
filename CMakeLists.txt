cmake_minimum_required(VERSION 3.10)

project(DocumentLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    Document.h
    Receipt.h
    Invoice.h
    Check.h
)

add_executable(lab7 ${SOURCES})