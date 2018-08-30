#ifndef VISION_BLOB_DETECTOR_HPP
#define VISION_BLOB_DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <vector>

namespace Vision {

class BlobDetector
{
public:
    explicit BlobDetector (cv::Mat const image);
    std::vector<cv::Mat> chromaticity ();
    cv::Mat grayscale_invariant (double theta);
    cv::Mat normalize (cv::Mat);

private:
    cv::Mat original_;
};

} // namespace Vision

#endif // VISION_BLOB_DETECTOR_HPP