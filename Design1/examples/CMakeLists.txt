#-------------------------------------------------------------------------------
# webcam_picture
#-------------------------------------------------------------------------------

add_executable(webcam_picture
    webcam_picture.cpp
)
target_link_libraries(webcam_picture PRIVATE
    Vision
)
target_compile_options(webcam_picture PRIVATE
    -std=c++14
)
set_target_properties(webcam_picture PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

#-------------------------------------------------------------------------------
# webcam_picture_edit
#-------------------------------------------------------------------------------

add_executable(webcam_picture_edit
    webcam_picture_edit.cpp
)
target_link_libraries(webcam_picture_edit PRIVATE
    Vision
)
target_compile_options(webcam_picture_edit PRIVATE
    -std=c++14
)
set_target_properties(webcam_picture_edit PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
