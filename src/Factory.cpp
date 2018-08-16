/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Factory.cpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Implement the concrete Factory classes.
*******************************************************************************/
#include "Vision/Factory.hpp"
#include "Vision/Camera.hpp"
#include "Vision/Display.hpp"

namespace Vision {

/*------------------------------ OpenCV Factory ------------------------------*/

Camera*
OpenCVFactory :: MakeCamera (int device_no)
{
    return new OpenCVCamera (device_no);
}

Display*
OpenCVFactory :: MakeDisplay (char const * title)
{
    return new OpenCVDisplay (title);
}

} // namespace Vision
