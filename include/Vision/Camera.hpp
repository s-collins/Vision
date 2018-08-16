/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Camera.hpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Defines an abstract base class for Camera objects. Also defines
            derived Camera classes. Clients should create Camera objects via
            the interface provided by the abstract factory (see Factory.hpp).
*******************************************************************************/
#ifndef VISION_CAMERA_HPP
#define VISION_CAMERA_HPP

#include <opencv2/opencv.hpp>

namespace Vision {

// Forward declare referenced types. Not necessary to #include because these
// types are only used by pointer or reference. Saves a little compile time.
class Image;

/*------------------------------- Base Camera --------------------------------*/

class Camera
{
public:
    virtual ~Camera () = default;
    virtual Image* TakePicture () = 0;
};

/*------------------------------ OpenCV Camera -------------------------------*/

class OpenCVCamera : public Camera
{
public:
    explicit OpenCVCamera (int device_no = 1);
    Image* TakePicture () override;

private:
    cv::VideoCapture video_capture_;
};

} // namespace Vision

#endif // VISION_CAMERA_HPP
