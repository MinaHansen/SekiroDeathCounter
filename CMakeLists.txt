cmake_minimum_required(VERSION 3.28.0)
project(SekiroDeathCounter)

set(CMAKE_CXX_STANDARD 17)

add_executable(SekiroDeathCounter main.cpp
        ProcReader.cpp
        ProcReader.h
        ProcReader.h
        ProcGetter.cpp
        ProcGetter.h
        DeathCounter.cpp
        DeathCounter.h)
