cmake_minimum_required(VERSION 3.16)
project(qlang2)

set(CMAKE_CXX_STANDARD 20)

#list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/llvm-project/llvm/cmake/modules")
#set(LLVM_DIR "${PROJECT_SOURCE_DIR}/llvm-project/llvm/cmake/modules")
#find_package(LLVM REQUIRED CONFIG)

add_subdirectory(llvm-project/llvm)
include_directories(llvm-project/llvm/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/llvm-project/llvm/include)
#separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
#add_definitions(${LLVM_DEFINITIONS_LIST})

add_subdirectory(pegtl)
include_directories(pegtl/include)

#add_llvm_executable(q2 main.cpp)
add_executable(q2 main.cpp)
llvm_map_components_to_libnames(llvm_libs support core nativecodegen)
target_link_libraries(q2 PRIVATE taocpp::pegtl ${llvm_libs})
