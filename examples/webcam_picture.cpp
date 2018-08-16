/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : webcam_picture.cpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Demonstrate usage of the Vision framework to capture an image from
            a computer's built-in camera and display this image in a window.
*******************************************************************************/
#include "Vision/Camera.hpp"
#include "Vision/Display.hpp"
#include "Vision/Factory.hpp"
#include "Vision/Image.hpp"
#include <memory>

int main ()
{
    using namespace Vision;
    using namespace std;

    // Create the factory
    unique_ptr<Factory> factory = make_unique<OpenCVFactory>();

    // Make the camera
    // (0 -> built-in camera; 1 -> auxiliary camera)
    unique_ptr<Camera> camera { factory->MakeCamera(Camera::BUILT_IN_CAM) };

    // Make the display
    unique_ptr<Display> display { factory->MakeDisplay("Webcam Example") };

    // Take a picture
    unique_ptr<Image> image { camera->TakePicture() };

    // Display the picture
    display->show(*image);
}