add_library (
    Vision
    File.cpp
    BlobDetector.cpp
)
target_link_libraries (
    Vision
    PRIVATE # External Libraries
    ${OpenCV_LIBS}
)
target_compile_options (
    Vision
    PRIVATE
    -std=c++11
)
target_include_directories (
    Vision
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)