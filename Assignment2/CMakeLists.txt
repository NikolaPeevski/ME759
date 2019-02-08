cmake_minimum_required(VERSION 3.08)

project(Assignment2)
set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(problem1a problem1a.c)
add_executable(problem1b problem1b.c)
add_executable(problem2 problem2a.c)
add_executable(problem3a problem3a.c)
add_executable(problem3b problem3b.c)
