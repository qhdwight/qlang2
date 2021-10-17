cmake_minimum_required(VERSION 3.16)
project(q2)

add_subdirectory(pegtl)
add_subdirectory(llvm-project/llvm)

include_directories(llvm-project/llvm/include)
include_directories(pegtl/include)

set(CMAKE_CXX_STANDARD 20)

add_executable(q2 main.cpp)
