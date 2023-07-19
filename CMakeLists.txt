cmake_minimum_required(VERSION 3.21)
project(MonotoneCubicInterpolation)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_subdirectory(hermite)
include_directories(hermite/include)

# add_subdirectory(app)