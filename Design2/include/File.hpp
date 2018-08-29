#ifndef VISION_FILE_HPP
#define VISION_FILE_HPP
#include <opencv2/opencv.hpp>

namespace Vision {

////////////////////////////////////////////////////////////////////////////////
/// brief         : Opens an image file.
///-----------------------------------------------------------------------------
/// preconditions :  - 'filename' is a path relative to the location of the
///                    executable, and it uniquely identifies an image file
///                    (including an extension)
///                  - 'filename' has one of the following extensions/formats:
///                    .jpeg, .jpg, .png, .tiff
///-----------------------------------------------------------------------------
/// postconditions : - Throws a std::runtime_error exception if the specified
///                    file could not be opened.
///-----------------------------------------------------------------------------
/// returns        : - Returns a object of type cv::Mat, which is a class from
///                    the OpenCV library that represents matrices.
///                  - First matrix dimension is rows, and second is columns,
///                    and third is intensities of each of the color channels
///                    (Red channel, Blue channel, and Green channel)
////////////////////////////////////////////////////////////////////////////////
cv::Mat OpenImage (char const * filename);
  
//TODO: std::vector<cv::Mat> OpenVideo (char const *);

} // namespace Vision

#endif // VISION_FILE_HPP