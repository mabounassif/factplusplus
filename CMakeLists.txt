cmake_minimum_required(VERSION 2.8.11)
project(factplusplus)

# global definition
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ffast-math -fPIC -fomit-frame-pointer")
# Additional warnings (from GCC 6.2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wsuggest-override")

add_subdirectory(Kernel)
add_subdirectory(FaCT++)
add_subdirectory(FaCT++.C)
add_subdirectory(FaCT++.JNI)
