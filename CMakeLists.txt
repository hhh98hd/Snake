CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_GCC_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
PROJECT(Snake)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set(SOURCES
    ${SRC_DIR}/GameModel.cpp
    ${SRC_DIR}/KeyHandler.cpp
    ${SRC_DIR}/Renderer.cpp
    ${SRC_DIR}/Snake.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(game game.cpp ${SOURCES})
