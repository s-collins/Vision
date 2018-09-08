#include "File.hpp"
#include "BlobDetector.hpp"
#include <opencv2/opencv.hpp>
#include <cstdint>

//******************************************************************************
// GetBlobs 
//
// Notes: Detects blobs with given diameter in the given source image.
//
//******************************************************************************
cv::Mat1b
GetBlobs (cv::Mat invariant, uint16_t diameter)
{
    // Sigma1 should be radius / sqrt(2)
    double sigma_1 = diameter / 2.82;
    double sigma_2 = 0.8 * sigma_1;

    // Create the Gaussian Filters
    auto k1 = cv::getGaussianKernel(diameter, sigma_1, CV_32F);
    auto k2 = cv::getGaussianKernel(diameter, sigma_2, CV_32F);
    cv::Size s = invariant.size();
    cv::Mat gauss1 (s.height, s.width, CV_32F);
    cv::Mat gauss2 (s.height, s.width, CV_32F);

    // Apply the Gaussian Filters
    cv::sepFilter2D(invariant, gauss1, CV_32F, k1, k1);
    cv::sepFilter2D(invariant, gauss2, CV_32F, k2, k2);

    // Subtract the filter outputs in order to approximate Laplacian
    cv::Mat output = gauss1 - gauss2;

    // Normalize the output to the range [0, 255]
    cv::normalize(output, output, 0, 255, cv::NORM_MINMAX);

    // Threshold
    cv::threshold(output, output, 120, 255, CV_8U);

    return output;
}

int main () {

    auto image = Vision::OpenImage("test.png");
    Vision::BlobDetector detector (image);
    auto invariant = detector.grayscale_invariant(145);

    for (int i = 1; i < 250; i += 2) {
        cv::Mat output = GetBlobs(invariant, i);
        cv::imshow("blobs", output);
        cv::waitKey(10);
        std::cout << i << std::endl;
    }

    return 0;
}