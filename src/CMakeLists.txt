cmake_minimum_required(VERSION 3.13)
project(WBS_SucheA_A1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

add_executable(WBS_SucheA_A1 main.cpp lib/Playground.cpp lib/Playground.h lib/Artifact.cpp lib/Artifact.h lib/State.cpp lib/State.h lib/Helper.cpp lib/Helper.h lib/PriorityQueue.cpp lib/PriorityQueue.h)