cmake_minimum_required(VERSION 3.27)
project(KV1)

set(CMAKE_CXX_STANDARD 17)

add_executable(KV1 main.cpp
        Tree.cpp
        Tree.h
        ControlPanel.cpp
        ControlPanel.h
        Floor.cpp
        Floor.h
        InputObject.cpp
        InputObject.h
        Lift.cpp
        Lift.h
        OutputObject.cpp
        OutputObject.h
        Passenger.cpp
        Passenger.h
        System.cpp
        System.h
)
