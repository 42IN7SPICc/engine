cmake_minimum_required(VERSION 3.20)
project(spic-engine)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} SHARED engine.cpp)
