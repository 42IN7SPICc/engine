cmake_minimum_required(VERSION 3.20)
project(spic-engine)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/includes)

include_directories(${PROJECT_INCLUDES_DIR}/spic-api-headers)

file(GLOB_RECURSE SOURCE src/*.cpp ${PROJECT_INCLUDES_DIR}/spic-api-headers/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE})
