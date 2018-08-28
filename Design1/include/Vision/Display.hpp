/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Display.hpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Defines an abstract base class for Display objects. Also defines
            derived Display classes. Clients should create Display objects via
            the interface provided by the abstract factory (see Factory.hpp).
*******************************************************************************/
#ifndef VISION_DISPLAY_HPP
#define VISION_DISPLAY_HPP

#include <string>

namespace Vision {

// Forward declare referenced types. Not necessary to #include because these
// types are only used by pointer or reference. Saves a little compile time.
class Image;

/*------------------------------- Display Base -------------------------------*/

class Display
{
public:
    virtual ~Display () = default;
    virtual void show (Image const &) = 0;
};

/*------------------------------ OpenCV Display ------------------------------*/

class OpenCVDisplay : public Display
{
public:
    OpenCVDisplay (char const * title);
    void show (Image const &) override;

private:
    std::string title_;
};

} // namespace Vision

#endif // VISION_DISPLAY_HPP
