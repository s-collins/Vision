/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Display.cpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Implement the concrete Display classes.
*******************************************************************************/
#include "Vision/Display.hpp"
#include "Vision/Image.hpp"
#include <opencv2/opencv.hpp>

namespace Vision {

OpenCVDisplay :: OpenCVDisplay (char const * title)
: title_{title}
{}

void
OpenCVDisplay :: show (Image const & image)
{
    // This dynamic cast is appropriate because the factory enforces the
    // design that OpenCV objects are to be used with other OpenCV objects.
    auto cv_image = dynamic_cast<OpenCVImage const &>(image);

    cv::imshow(title_.c_str(), cv_image.GetMatrix());
    cv::waitKey(0);
}

} // namespace Vision