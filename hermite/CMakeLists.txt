cmake_minimum_required(VERSION 3.21)
project(MonotoneCubicInterpolationApp)


set(CMAKE_CXX_STANDARD 14)



include_directories(
        include
)

add_library(
        ${PROJECT_NAME}
        src/base/cubic_hermite_spline.cpp
        include/base/cubic_hermite_spline.h
        src/monotone_cubic_interpolation.cpp
        include/monotone_cubic_interpolation.h
        include/base/cubic_interpolation.h
        src/hermite_cubic_interpolation.cpp
        include/hermite_cubic_interpolation.h
        include/base/misc.h
)

add_executable(
        HermitDemo
        demo/hermite_demo.cpp

        src/base/cubic_hermite_spline.cpp

        include/base/cubic_hermite_spline.h
        include/base/cubic_interpolation.h

        src/monotone_cubic_interpolation.cpp
        include/monotone_cubic_interpolation.h

        src/hermite_cubic_interpolation.cpp
        include/hermite_cubic_interpolation.h

        include/base/misc.h
)

add_executable(
        MonotoneTest1
        tests/monotone_cubic_test_1.cpp
        src/base/cubic_hermite_spline.cpp
        include/base/cubic_hermite_spline.h
        src/monotone_cubic_interpolation.cpp
        include/monotone_cubic_interpolation.h
        include/base/cubic_interpolation.h
        include/base/misc.h
)

add_executable(
        MonotoneTest2
        tests/monotone_cubic_test_2.cpp
        src/base/cubic_hermite_spline.cpp
        include/base/cubic_hermite_spline.h
        src/monotone_cubic_interpolation.cpp
        include/base/cubic_interpolation.h
        include/monotone_cubic_interpolation.h
        include/base/misc.h
)


add_executable(
        MonotoneTest3
        tests/monotone_cubic_test_3.cpp
        src/base/cubic_hermite_spline.cpp
        include/base/cubic_hermite_spline.h
        src/monotone_cubic_interpolation.cpp
        include/base/cubic_interpolation.h
        include/monotone_cubic_interpolation.h
        include/base/misc.h
)

add_executable(
        MonotoneTest4
        tests/monotone_cubic_test_4.cpp
        src/base/cubic_hermite_spline.cpp
        include/base/cubic_hermite_spline.h
        include/base/cubic_interpolation.h
        include/monotone_cubic_interpolation.h
        src/monotone_cubic_interpolation.cpp
        include/base/misc.h
)


add_executable(
        MonotoneLoopTest
        tests/monotone_cubic_loop_test.cpp
        src/base/cubic_hermite_spline.cpp
        include/base/cubic_interpolation.h
        include/base/cubic_hermite_spline.h
        include/monotone_cubic_interpolation.h
        src/monotone_cubic_interpolation.cpp
        include/base/misc.h
)



target_link_libraries(
        ${PROJECT_NAME}
)


add_test(NAME MonotoneTest1 COMMAND MonotoneTest1)
add_test(NAME MonotoneTest2 COMMAND MonotoneTest2)
add_test(NAME MonotoneTest3 COMMAND MonotoneTest3)
add_test(NAME MonotoneTest4 COMMAND MonotoneTest4)

add_test(NAME MonotoneLoopTest COMMAND MonotoneLoopTest)


