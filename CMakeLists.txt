cmake_minimum_required(VERSION 3.10)

file(READ "VERSION" VER_FROM_FILE)
string(STRIP "${VER_FROM_FILE}" VERSION_TAG)
project(CalculatorApp VERSION ${VERSION_TAG} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(APP_VERSION="${VERSION_TAG}")

enable_testing()
add_executable(calculator src/main.cpp)
add_executable(run_tests tests/test_calc.cpp)
add_test(NAME TesteSoma COMMAND run_tests)
