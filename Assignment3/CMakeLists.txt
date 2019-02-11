cmake_minimum_required(VERSION 3.08)

project(Assignment3)
set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 14)
#enable_language(CUDA)

include_directories(.)

#add_executable(problem3 problem3.cu)
add_executable(problem1 problem1.c)