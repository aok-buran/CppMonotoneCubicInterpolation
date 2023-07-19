cmake_minimum_required(VERSION 3.21)
project(MonotoneCubicInterpolation)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_subdirectory(hermit)
include_directories(hermit/include)

# add_subdirectory(app)