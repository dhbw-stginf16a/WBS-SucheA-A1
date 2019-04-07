cmake_minimum_required(VERSION 3.13)
project(WBS_SucheA_A1)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp lib/Playground.cpp lib/Playground.h lib/Artefact.cpp lib/Artefact.h lib/State.cpp lib/State.h lib/Helper.cpp lib/Helper.h)