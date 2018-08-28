cmake_minimum_required(VERSION 3.0)
project(Vision)

find_package(OpenCV REQUIRED)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)