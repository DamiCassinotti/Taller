cmake_minimum_required(VERSION 3.8)
project(TP2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/EchoProcessor.cpp
        src/EchoProcessor.h
        src/LineProcessor.cpp
        src/LineProcessor.h
        src/test.cpp)

add_executable(TP2 ${SOURCE_FILES})