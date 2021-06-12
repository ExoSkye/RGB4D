project(RGB4D_LLVM LANGUAGES CXX VERSION 1.0.0)

find_package(LLVM REQUIRED)

add_executable(RGB4DCompiler main.cpp pch.h)



