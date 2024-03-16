cmake_minimum_required(VERSION 3.27)
project(Rational_Numbers_Calc)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()

add_executable(Rational_Numbers_Calc main.cpp
        test.cpp)
