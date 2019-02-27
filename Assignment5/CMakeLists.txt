cmake_minimum_required(VERSION 3.08)

project(Assignment5)
set (CMAKE_C_FLAGS "-std=c99 -lm")
set(CMAKE_CXX_STANDARD 14)
enable_language(CUDA)

include_directories(.)

add_executable(problem2 problem2.cu ../randoms/randoms.c)
#add_executable(problem3 problem3.cu randoms.c)
