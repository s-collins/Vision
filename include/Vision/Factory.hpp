/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Factory.hpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Defines factories for instantiating the key abstractions in the
            Computer Vision framework for the UA NASA Robotic Mining
            Competition Team's robot. An abstract "Base Factory" specifies the
            interface supplied by all the concrete factories. Clients should
            program against this interface. The factories will be used to create
            families of related application objects. By deriving new classes
            from the base classes in the Vision framework, developers can
            experiment with different implementations.
*******************************************************************************/
#ifndef VISION_FACTORY_HPP
#define VISION_FACTORY_HPP

namespace Vision {

// Forward declare referenced types. Not necessary to #include because these
// types are only used by pointer or reference. Saves a little compile time.
class Camera;
class Display;
class Editor;

/*------------------------------- Base Factory -------------------------------*/

class Factory
{
public:
    virtual Camera*  MakeCamera  (int)           = 0;
    virtual Display* MakeDisplay (char const *)  = 0;
    virtual Editor*  MakeEditor  ()              = 0;
};

/*------------------------------ OpenCV Factory ------------------------------*/

class OpenCVFactory : public Factory
{
public:
    Camera*  MakeCamera  (int)          override;
    Display* MakeDisplay (char const *) override;
    Editor*  MakeEditor  ()             override;
};

} // namespace Vision

#endif // VISION_FACTORY_HPP
