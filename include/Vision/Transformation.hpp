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

#include <cstddef>
#include <tuple>
#include <vector>

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

class Grayscale : public Transformation
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

/*----------------------- Statistical Transformations ------------------------*/

class Statistical : public Transformation
{
public:
    explicit Statistical (size_t boxsize);
    virtual void apply (Image &) = 0;

protected:
    class Box
    {
    public:
        Box (size_t top, size_t bottom, size_t left, size_t right);
        bool Contains (size_t row, size_t col) const;
        size_t Top    () const {return top_;}
        size_t Bottom () const {return bottom_;}
        size_t Left   () const {return left_;}
        size_t Right  () const {return right_;}
        size_t Size   () const {return (bottom_ - top_ + 1) * (right_ - left_ + 1);}

        using RGB_Tuple = std::tuple<uint8_t, uint8_t, uint8_t>;
        RGB_Tuple Average (Image &) const;
        RGB_Tuple StDev   (Image &) const;

    private:
        size_t top_, bottom_, left_, right_;
    };
    std::vector<Box> GetBoxes (Image const &) const;

private:
    size_t boxsize_;
};

class Average : public Statistical
{
public:
    explicit Average (size_t boxsize);
    void apply (Image &) override;
};

class StandardDeviation : public Statistical
{
public:
    explicit StandardDeviation (size_t boxsize);
    void apply (Image &) override;
};

} // namespace Vision

#endif // VISION_TRANSFORMATION_HPP
