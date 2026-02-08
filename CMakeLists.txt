cmake_minimum_required(VERSION 3.10)

project(CalculatorApp VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(calculator src/main.cpp)

add_executable(run_tests tests/test_calc.cpp)

add_test(NAME TesteSoma COMMAND run_tests)
