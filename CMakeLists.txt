cmake_minimum_required(VERSION 3.10)

project(gb-emulator LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)


# get all sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

file(COPY "resources" DESTINATION ${CMAKE_BINARY_DIR})

add_library(core
        ${SOURCES}
        include/gameboy.h
        src/gameboy.cpp
        include/twobytes.h
        src/instructions/jumps_subroutines.cpp
        src/instructions/8bit_arithemetic_logic.cpp
        src/instructions/load.cpp
        src/instructions/bit_shift.cpp
        src/instructions/16bit_arithmetic.cpp
        src/instructions/stack_operation.cpp
        src/instructions/misc.cpp
        src/instructions/flag_utils.cpp
        include/register_bindings.h
        include/cpu.h
        src/cpu.cpp
)

target_include_directories(core PUBLIC include)

# target executable
add_executable(gb-emulator src/main.cpp)
target_link_libraries(gb-emulator PUBLIC core)

# include own headers

include(GoogleTest)

enable_testing()
add_executable(unit-test test/test_main.cpp
        test/load_test.cpp
        test/register_pair_test.cpp
        test/math_test.cpp
        test/flag_test.cpp
        test/bit_shift_test.cpp
        test/jumps_test.cpp
        test/subroutines_test.cpp
)
target_link_libraries(unit-test PUBLIC gtest gtest_main)
target_link_libraries(unit-test PUBLIC core)

