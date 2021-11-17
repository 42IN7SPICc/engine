cmake_minimum_required(VERSION 3.16)
project(spic-engine)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/includes)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

include_directories(${PROJECT_INCLUDES_DIR}/spic-api-headers)

file(GLOB_RECURSE SOURCE src/*.cpp ${PROJECT_INCLUDES_DIR}/spic-api-headers/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_image SDL2::SDL2_mixer SDL2::SDL2_ttf box2d::box2d)

add_executable(${PROJECT_NAME}-exec main.cpp TestApplyForce.cpp TestApplyForceReverse.cpp)
target_link_libraries(${PROJECT_NAME}-exec ${PROJECT_NAME})