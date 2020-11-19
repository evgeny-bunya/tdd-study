cmake_minimum_required(VERSION 3.10)
project(tdd CXX)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -pedantic")
endif()

set(CMAKE_CXX_CPPCHECK "cppcheck;--enable=warning,style,performance,portability;--std=c++14")

set(GTEST_ROOT "googletest")

add_library(currency_lib
            Currency.hpp
            Currency.cpp)

add_executable(${PROJECT_NAME}
               main.cpp)

include_directories(googletest/include)

add_executable(cur_test
               currency_test.cpp)
target_link_libraries(cur_test currency_lib gtest_main)

enable_testing()
add_test(cur_test cur_test)
