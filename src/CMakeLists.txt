add_library(Vision
    Camera.cpp
    Display.cpp
    Editor.cpp
    Factory.cpp
    FileManager.cpp
    Image.cpp
    Transformation.cpp
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
set_target_properties(Vision PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
)