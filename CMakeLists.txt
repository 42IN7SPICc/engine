cmake_minimum_required(VERSION 3.16)
project(spic-engine)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/includes)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(cereal CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

include_directories(${PROJECT_INCLUDES_DIR}/spic-api-headers)
include_directories(${PROJECT_INCLUDES_DIR}/Engine)

file(GLOB_RECURSE SOURCE src/*.cpp ${PROJECT_INCLUDES_DIR}/spic-api-headers/*.cpp)
file(GLOB_RECURSE TEST_SOURCE tests/*.cpp tests/*.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_image SDL2::SDL2_mixer SDL2::SDL2_ttf box2d::box2d)
target_link_libraries(${PROJECT_NAME} INTERFACE cereal)

set(PROJECT_NAME_TESTS ${PROJECT_NAME}-tests)
add_executable(${PROJECT_NAME_TESTS} ${TEST_SOURCE})
add_dependencies(${PROJECT_NAME_TESTS} ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME_TESTS} PRIVATE ${PROJECT_NAME} GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
gtest_discover_tests(${PROJECT_NAME_TESTS})

add_executable(${PROJECT_NAME}-exec main.cpp)
target_link_libraries(${PROJECT_NAME}-exec ${PROJECT_NAME})