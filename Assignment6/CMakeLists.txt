cmake_minimum_required(VERSION 3.08)
set(CMAKE_CUDA_HOST_COMPILER $ENV{CU_CCBIN} CACHE PATH "Cuda host compiler dir")
project(Assignment5)
set (CMAKE_C_FLAGS "-std=c99 -lm")
set(CMAKE_CXX_STANDARD 14)
enable_language(CUDA)

include_directories(.)

add_executable(problem2 problem2.cu ../randoms/randoms.c)
add_executable(problem1 matrixadd.cu matrixadd.h matrixadd_gold.cpp)
