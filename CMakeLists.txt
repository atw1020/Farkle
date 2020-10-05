cmake_minimum_required(VERSION 3.17)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 main.cpp scorer.cpp scorer.h die.cpp die.h Player.cpp Player.h AI.cpp AI.h IO.cpp IO.h Game.cpp Game.h stats.cpp stats.h)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})