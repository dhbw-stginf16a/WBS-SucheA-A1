cmake_minimum_required(VERSION 3.11)
project(WBS_SucheA_A1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -static-libgcc -static-libstdc++")

add_executable(WBS_SucheA_A1 main.cpp lib/Playground.cpp lib/Playground.h lib/Component.cpp lib/Component.h lib/State.cpp lib/State.h lib/Helper.cpp lib/Helper.h lib/PriorityQueue.cpp lib/PriorityQueue.h)