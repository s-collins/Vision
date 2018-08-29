project(Vision)
cmake_minimum_required(VERSION 3.0)

add_subdirectory(src)

find_package(OpenCV REQUIRED)

# Testing main function
add_executable(main main.cpp)
target_link_libraries(main PRIVATE Vision ${OpenCV_LIBS})
target_include_directories(main PRIVATE include)
target_compile_options(main PRIVATE -std=c++11)