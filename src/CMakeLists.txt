add_library(Vision
    Camera.cpp
    Display.cpp
    Factory.cpp
    Image.cpp
)
target_link_libraries(Vision PRIVATE
    ${OpenCV_LIBS}
)
target_compile_options(Vision PRIVATE
    -std=c++11
)
target_include_directories(Vision PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)