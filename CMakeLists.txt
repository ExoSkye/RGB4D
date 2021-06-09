cmake_minimum_required(VERSION 3.10)
project(RGB4D LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_IDE "Builds the IDE" ON)

add_executable(RGB4D_Interpreter interpreter/main.cpp interpreter/pch.h interpreter/commands.h interpreter/file.h)
if(BUILD_IDE)
    add_subdirectory(ide)
endif()
