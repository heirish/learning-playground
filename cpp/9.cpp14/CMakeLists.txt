cmake_minimum_required(VERSION 3.22.1)
set(compoent_name CPP14)
project(${compoent_name})

include_directories(.)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(${compoent_name} 
main.cpp
)
