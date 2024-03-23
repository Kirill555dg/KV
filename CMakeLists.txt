cmake_minimum_required(VERSION 3.27)
project(KV1)

set(CMAKE_CXX_STANDARD 17)

add_executable(KV1 main.cpp
        Tree.cpp
        Tree.h
        Root.cpp
        Root.h)
