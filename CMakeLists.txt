cmake_minimum_required(VERSION 3.10)

project(gb-emulator LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# get all sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

# target executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES}
        include/registers.h
)

# include own headers
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)