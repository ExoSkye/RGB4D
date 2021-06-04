cmake_minimum_required(VERSION 3.20)
project(PPEN)

set(CMAKE_CXX_STANDARD 20)

add_executable(PPEN main.cpp pch.h commands.h file.h)