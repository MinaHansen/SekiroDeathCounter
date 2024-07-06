cmake_minimum_required(VERSION 3.28.0)
project(SekiroDeathCounter)

set(CMAKE_CXX_STANDARD 17)

add_executable(SekiroDeathCounter WIN32 main.cpp
        DeathCounter.cpp
        Overlay.cpp
        ProcGetter.cpp
        ProcReader.cpp)
