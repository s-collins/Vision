/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Editor.hpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Defines a base class for the Editor abstraction, which represents
            an ordered sequence of transformations that can be applied to an
            image. The client should create the editor via the interface
            provided by the factory (see Factory.hpp).
*******************************************************************************/
#ifndef VISION_EDITOR_HPP
#define VISION_EDITOR_HPP

#include <vector>

namespace Vision {

// Forward declare referenced types. Not necessary to #include because these
// types are only used by pointer or reference. Saves a little compile time.
class Image;
class Transformation;

/*------------------------------- Editor Base --------------------------------*/

class Editor
{
public:
    virtual ~Editor ();

    virtual void add  (Transformation *);
    virtual void edit (Image &);

private:
    std::vector<Transformation *> transforms_;
};

/*------------------------------ OpenCV Editor -------------------------------*/

// This class will be able to apply special kinds of transformations,
// which will have access to the underlying Mat3b object contained inside
// of the OpenCVImage. These additional edits will be represented by
// private methods of the OpenCVEditor, and they will be applied inside
// the overridden "edit" method.
class OpenCVEditor : public Editor
{
public:
    void edit (Image &) override;

private:
    // TODO: Add special methods here, which are able to exploit features of the
    // OpenCV library.
};

} // namespace Vision

#endif // VISION_EDITOR_HPP
