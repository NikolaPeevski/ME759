cmake_minimum_required(VERSION 3.13)
project(ME759)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Assigment2)
include_directories(Assignment1)
include_directories(cmake-build-debug)

add_executable(ME759
        Assigment2/problem1a.dSYM/Contents/Resources/DWARF/problem1a
        Assigment2/problem1a.dSYM/Contents/Info.plist
        Assigment2/problem1b.dSYM/Contents/Resources/DWARF/problem1b
        Assigment2/problem1b.dSYM/Contents/Info.plist
        Assigment2/problem2a.dSYM/Contents/Resources/DWARF/problem2a
        Assigment2/problem2a.dSYM/Contents/Info.plist
        Assigment2/Makefile
        Assigment2/problem1.in
        Assigment2/problem1a
        Assigment2/problem1a.c
        Assigment2/problem1b
        Assigment2/problem1b.c
        Assigment2/problem2a
        Assigment2/problem2a.c
        Assignment1/handin/problem3.dSYM/Contents/Resources/DWARF/problem3
        Assignment1/handin/problem3.dSYM/Contents/Info.plist
        Assignment1/handin/Makefile
        Assignment1/handin/problem1
        Assignment1/handin/problem1.c
        Assignment1/handin/problem1.txt
        Assignment1/handin/problem2
        Assignment1/handin/problem2.c
        Assignment1/handin/problem3
        Assignment1/handin/problem3.cpp
        Assignment1/handin/problem3.out
        Assignment1/o.out.dSYM/Contents/Resources/DWARF/o.out
        Assignment1/o.out.dSYM/Contents/Info.plist
        Assignment1/output.dSYM/Contents/Resources/DWARF/output
        Assignment1/output.dSYM/Contents/Info.plist
        Assignment1/CMakeLists.txt
        Assignment1/problem1.c
        Assignment1/problem1.txt
        Assignment1/problem2.c
        Assignment1/problem3.cpp
        Assignment1/problem3.out
        Assignment1/problem3.txt
        Assignment1/testing.c
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/ME759
        cmake-build-debug/ME759.cbp
        cmake-build-debug/student.txt
        README.md)
