cmake_minimum_required(VERSION 3.20)
project(spic-engine)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/includes)

include_directories(${PROJECT_INCLUDES_DIR}/spic-api-headers)

add_library(${PROJECT_NAME} SHARED engine.cpp)
