#include "File.hpp"
#include "BlobDetector.hpp"
#include <opencv2/opencv.hpp>

int main () {
    auto image = Vision::OpenImage("test.png");


    for (int i = 0; i < 360; ++i)
    {

    Vision::BlobDetector detector (image);
    auto invariant = detector.grayscale_invariant(i); // Best angle is approx. 150

    // Difference of guassian
    cv::Mat a, b;
    int sigma1 = 151;
    int sigma2 = 141;
    cv::GaussianBlur(invariant, a, cv::Size{sigma1, sigma1}, 0);
    cv::GaussianBlur(invariant, b, cv::Size{sigma2, sigma2}, 0);
    auto output = detector.normalize(a - b);
    //imshow("blobs", output);
    //cv::waitKey(0);

    cv::threshold(output, output, 128, 255, 0);
    //cv::erode(output, output, cv::getStructuringElement(cv::MORPH_RECT, {30, 30}, {5, 5}));
    imshow("blobs", output);
    cv::waitKey(10);

    }

    return 0;
}