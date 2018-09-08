#include "BlobDetector.hpp"
#include <cstdint>
#include <cmath>

namespace Vision {

BlobDetector :: BlobDetector (cv::Mat image)
: original_{image} {}

std::vector<cv::Mat> BlobDetector :: chromaticity ()
{
    // determine indices of the other channels
    int base = 1; // green
    int x = 2;    // red
    int y = 0;    // blue

    cv::Size s = original_.size();
    std::vector<cv::Mat> output;
    output.push_back(cv::Mat(s.height, s.width, CV_32FC1));
    output.push_back(cv::Mat(s.height, s.width, CV_32FC1));
    for (int i = 0; i < s.height; ++i)
        for (int j = 0; j < s.width; ++j) {
            auto pixel = original_.at<cv::Vec3b>(i, j);
            //std::cout << pixel[x] - pixel[y] << std::endl;
            output.at(0).at<float>(i, j) = log((float)pixel[x] / pixel[base]);
            output.at(1).at<float>(i, j) = log((float)pixel[y] / pixel[base]);
        }
    return std::move(output);
}

cv::Mat BlobDetector :: grayscale_invariant (double theta)
{
    // Convert theta from degrees to radians
    static double const PI = 3.141592;
    theta = theta * PI / 180;

    // Get the natural logarithm of the chromaticity
    auto c = chromaticity();
    
    // Project the coordinates onto the theta direction
    cv::Size s = c.at(0).size();
    cv::Mat invariant (s.height, s.width, CV_32FC1);
    float max = 0, min = 0;
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            float x = c.at(0).at<float>(i, j);
            float y = c.at(1).at<float>(i, j);
            float value = x * cos(theta) + y * sin(theta);
            max = value > max ? value : max;
            min = value < min ? value : min;
            invariant.at<float>(i, j) = value;
        }
    }

/*
    cv::Mat normalized (s.height, s.width, CV_8UC1);
    for (int i = 0; i < s.height; ++i)
        for (int j = 0; j < s.width; ++j)
            normalized.at<uint8_t>(i, j) = (invariant.at<float>(i, j) - min) * 255 / (max - min);
            */

    return invariant;
}

cv::Mat BlobDetector :: normalize (cv::Mat input)
{
    cv::Size s = input.size();

    // Find the minimum and maximum values
    float min = 0, max = 0;
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            auto value = input.at<float>(i, j);
            min = value < min ? value : min;
            max = value > max ? value : max;
        }
    }

    // Map the values to the range [0, 255]
    cv::Mat output (s.height, s.width, CV_32FC1);
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            auto value = input.at<float>(i, j);
            value = (value - min) * 255 / (max - min);
            output.at<float>(i, j) = value;
        }
    }
    return output;
}

} // namespace Vision