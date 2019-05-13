cmake_minimum_required(VERSION 3.10)
include_directories(/usr/include/c++/4.2.1/)
set(CMAKE_CXX_COMPILER " -lIrrlicht -lGL -std=c++14")
FILE(GLOB HDRS
        /usr/local/include/irr/*.h
        )
