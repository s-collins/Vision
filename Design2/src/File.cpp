#include "File.hpp"

namespace Vision {

cv::Mat OpenImage (char const * name)
{
    cv::Mat3b matrix = cv::imread(name, CV_LOAD_IMAGE_COLOR);
    if (matrix.empty())
        throw std::runtime_error {"Could not open file."};
    return matrix;
}

} // namespace Vision