#include "File.hpp"
#include "BlobDetector.hpp"
#include <opencv2/opencv.hpp>

int main () {
    auto image = Vision::OpenImage("test.png");
    //cv::imshow("test", image);
    //cv::waitKey(0);

    Vision::BlobDetector detector (image);
    for (int i = 0; i <= 180; ++i)
    {

    std::cout << i << " degrees" << std::endl;
    auto invariant = detector.grayscale_invariant(i);
    //imshow("invariant", invariant);
    //cv::waitKey(1);

    cv::GaussianBlur(invariant, invariant, cv::Size{91, 91}, 0);
    cv::Laplacian(invariant, invariant, 0, 7);
    imshow("blobs", invariant);
    cv::waitKey(20);
    }

    auto invariant = detector.grayscale_invariant(150);

    /* Difference of Gaussians
    cv::Mat a, b;
    cv::GaussianBlur(invariant, a, cv::Size{51, 51}, 61 / 2.575);
    cv::GaussianBlur(invariant, b, cv::Size{91, 91}, 91 / 2.575);
    auto result = a - b;
    imshow("a", a);
    imshow("b", b);
    imshow("a - b", result * 1000);
    cv::waitKey(0);
    */

    cv::GaussianBlur(invariant, invariant, cv::Size{91, 91}, 0);
    cv::Laplacian(invariant, invariant, 0, 7);
    imshow("blobs", invariant);
    cv::waitKey(0);

    return 0;
}