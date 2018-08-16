add_executable(webcam_picture
    webcam_picture.cpp
)
target_link_libraries(webcam_picture PRIVATE
    Vision
)
target_compile_options(webcam_picture PRIVATE
    -std=c++14
)