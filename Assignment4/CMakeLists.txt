cmake_minimum_required(VERSION 3.08)

project(Assignment3)
set (CMAKE_C_FLAGS "-std=c99 -lm")
set(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_C_FLAGS "-lm")
enable_language(CUDA)

include_directories(.)

add_executable(problem1 problem1.cu)
add_executable(problem2 problem2.cu randoms.c)
add_executable(problem3 problem3.cu randoms.c)
