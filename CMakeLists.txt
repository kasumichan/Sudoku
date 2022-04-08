cmake_minimum_required(VERSION 3.20)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sudoku main.cpp Cell.cpp Cell.h Board.cpp Board.h)
