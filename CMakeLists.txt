cmake_minimum_required(VERSION 3.20)
project(PPEN LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_IDE "Builds the IDE" ON)

add_executable(PPEN_Interpreter interpreter/main.cpp interpreter/pch.h interpreter/commands.h interpreter/file.h)
if(BUILD_IDE)
    add_subdirectory(ide)
endif()
