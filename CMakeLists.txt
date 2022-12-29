cmake_minimum_required(VERSION 3.21)
project(WordCount)

set(CMAKE_CXX_STANDARD 20)

add_executable(WordCount main.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(SOURCE_FILES main.cpp)
add_executable(WordCount1 ${SOURCE_FILES})
target_link_libraries(WordCount1 ${CMAKE_EXE_LINKER_FLAGS})