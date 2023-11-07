cmake_minimum_required(VERSION 3.16)
project(median LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(doctest REQUIRED)

add_executable(median src/MedianStore.cpp test/TestMedianStore.cpp)
add_executable(heap test/TestHeap.cpp)

add_compile_options(-Wall -Wextra -Werror)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
link_libraries(doctest::doctest)
