/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Transformation.hpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Defines an abstract base class for transformations that can be
            applied to images. This base class specifies an interface, to which
            all of the derived concrete classes must conform.
*******************************************************************************/
#ifndef VISION_TRANSFORMATION_HPP
#define VISION_TRANSFORMATION_HPP

namespace Vision {

// Forward declare referenced types. Not necessary to #include because these
// types are only used by pointer or reference. Saves a little compile time.
class Image;

/*--------------------------- Transformation Base ----------------------------*/

class Transformation
{
public:
    virtual void apply (Image &) = 0;
};

/*------------------------- Grayscale Transformation -------------------------*/

class GrayscaleTransformation : public Transformation
{
public:
    void apply (Image &) override;
};

/*----------------------------- AdjustBrightness -----------------------------*/

class AdjustBrightness : public Transformation
{
public:
    explicit AdjustBrightness (int offset);
    void apply (Image &) override;
private:
    int offset_;
};

/*------------------------------- InvertColors -------------------------------*/

class InvertColors : public Transformation
{
public:
    void apply (Image &) override;
};

} // namespace Vision

#endif // VISION_TRANSFORMATION_HPP
