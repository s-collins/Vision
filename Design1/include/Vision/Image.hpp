/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Image.hpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Defines an abstract base class for Image objects.  Also defines
            derived Image classes. Clients should create Image objects via the
            interface provided by the abstract factory (see Factory.hpp).
*******************************************************************************/
#ifndef VISION_IMAGE_HPP
#define VISION_IMAGE_HPP

#include <cstddef>
#include <cstdint>
#include <opencv2/opencv.hpp>

namespace Vision {

/*-------------------------------- Base Image --------------------------------*/

class Image {
public:
    virtual ~Image () = default;

    // Accessors
    virtual uint8_t GetRed    (size_t row, size_t col) const = 0;
    virtual uint8_t GetGreen  (size_t row, size_t col) const = 0;
    virtual uint8_t GetBlue   (size_t row, size_t col) const = 0;
    virtual size_t  GetWidth  () const = 0;
    virtual size_t  GetHeight () const = 0;

    // Mutators
    virtual void    SetRed   (size_t row, size_t col, uint8_t intensity) = 0;
    virtual void    SetGreen (size_t row, size_t col, uint8_t intensity) = 0;
    virtual void    SetBlue  (size_t row, size_t col, uint8_t intensity) = 0;
};

/*------------------------------- OpenCV Image -------------------------------*/

class OpenCVImage : public Image
{
public:
    // Creators
    explicit OpenCVImage (cv::Mat3b);

    // Accessors
    uint8_t GetRed    (size_t row, size_t col) const override;
    uint8_t GetGreen  (size_t row, size_t col) const override;
    uint8_t GetBlue   (size_t row, size_t col) const override;
    size_t  GetWidth  () const override;
    size_t  GetHeight () const override;

    // Access opencv matrix
    cv::Mat3b const & GetMatrix () const;

    // Mutators
    void    SetRed   (size_t row, size_t col, uint8_t intensity) override;
    void    SetGreen (size_t row, size_t col, uint8_t intensity) override;
    void    SetBlue  (size_t row, size_t col, uint8_t intensity) override;

private:
    // Helpers (for implementation)
    uint8_t GetColor (size_t row, size_t col, int channel) const;
    void    SetColor (size_t row, size_t col, int channel, uint8_t intensity);
    enum {BLUE_CHANNEL = 0, GREEN_CHANNEL = 1, RED_CHANNEL = 2};

private:
    cv::Mat3b cv_matrix_;
};

} // namespace Vision

#endif // VISION_IMAGE_HPP
