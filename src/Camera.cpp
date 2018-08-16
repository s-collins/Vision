/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Camera.cpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Implement the concrete Camera classes.
*******************************************************************************/
#include "Vision/Camera.hpp"
#include "Vision/Image.hpp"
#include <exception>

namespace Vision {

/*------------------------------ OpenCV Camera -------------------------------*/

OpenCVCamera :: OpenCVCamera (int device_no)
{
    assert(device_no == 0 || device_no == 1);
    video_capture_.open(device_no);
    if (!video_capture_.isOpened())
        throw std::runtime_error {"Camera could not be openened."};
}

Image*
OpenCVCamera :: TakePicture ()
{
    cv::Mat3b cv_matrix;
    video_capture_ >> cv_matrix;
    return new OpenCVImage (std::move(cv_matrix));
}

} // namespace Vision
