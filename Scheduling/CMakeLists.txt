cmake_minimum_required(VERSION 3.27)
project(Scheduling)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Scheduling
        FCFS.cpp
        main.cpp
        Priority.cpp
        PriorityRR.cpp
        RR.cpp
        Scheduler.cpp
        Scheduler.h
        SJF.cpp)
