cmake_minimum_required(VERSION 3.31)
project(DLLNew)

set(CMAKE_CXX_STANDARD 20)

add_library(DLLNew SHARED library.cpp
        library.cpp
        library.h
)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()
