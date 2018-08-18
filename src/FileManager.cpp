#include "Vision/FileManager.hpp"
#include <opencv2/opencv.hpp>

namespace Vision {

/*---------------------------- OpenCV FileManager ----------------------------*/

Image*
OpenCVFileManager :: OpenImage (std::string path)
{
    cv::Mat3b cv_matrix = cv::imread(path, CV_LOAD_IMAGE_COLOR);
    if (cv_matrix.empty())
        throw std::runtime_error {"Could not load image."};
    return new OpenCVImage (cv_matrix);
}

void
OpenCVFileManager :: SaveImage (std::string path, Image const & image)
{
    cv::Mat3b cv_matrix = dynamic_cast<OpenCVImage const &>(image).GetMatrix();
    cv::imwrite(path, cv_matrix);
}

} // namespace Vision
