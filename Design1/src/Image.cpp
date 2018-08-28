/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Image.cpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Implement the concrete Image classes.
*******************************************************************************/
#include "Vision/Image.hpp"

namespace Vision {

/*------------------------------- OpenCV Image -------------------------------*/

OpenCVImage :: OpenCVImage (cv::Mat3b cv_matrix)
: cv_matrix_{std::move(cv_matrix)}
{}

uint8_t
OpenCVImage :: GetRed (size_t r, size_t c) const
{
    return GetColor(r, c, RED_CHANNEL);
}

uint8_t
OpenCVImage :: GetGreen (size_t r, size_t c) const
{
    return GetColor(r, c, GREEN_CHANNEL);
}

uint8_t
OpenCVImage :: GetBlue (size_t r, size_t c) const
{
    return GetColor(r, c, BLUE_CHANNEL);
}

size_t
OpenCVImage :: GetWidth () const
{
    return static_cast<size_t>(cv_matrix_.cols);
}

size_t
OpenCVImage :: GetHeight () const
{
    return static_cast<size_t>(cv_matrix_.rows);
}

cv::Mat3b const &
OpenCVImage :: GetMatrix () const
{
    return cv_matrix_;
}

void
OpenCVImage :: SetRed (size_t r, size_t c, uint8_t red)
{
    SetColor(r, c, RED_CHANNEL, red);
}

void
OpenCVImage :: SetGreen (size_t r, size_t c, uint8_t green)
{
    SetColor(r, c, GREEN_CHANNEL, green);
}

void
OpenCVImage :: SetBlue (size_t r, size_t c, uint8_t blue)
{
    SetColor(r, c, BLUE_CHANNEL, blue);
}

uint8_t
OpenCVImage :: GetColor (size_t r, size_t c, int channel) const
{
    auto row = static_cast<int>(r);
    auto col = static_cast<int>(c);
    return cv_matrix_.at<cv::Vec3b>(cv::Point(col, row))[channel];
}

void
OpenCVImage :: SetColor (size_t r, size_t c, int channel, uint8_t intensity)
{
    auto row = static_cast<int>(r);
    auto col = static_cast<int>(c);
    cv_matrix_.at<cv::Vec3b>(cv::Point(col, row))[channel] = intensity;
}

} // namespace Vision
