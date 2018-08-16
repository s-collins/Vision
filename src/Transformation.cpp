/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Transformation.cpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Implements the transformations that can be applied to images.
*******************************************************************************/
#include "Vision/Transformation.hpp"
#include "Vision/Image.hpp"

namespace Vision {

/*-------------------------------- Grayscale ---------------------------------*/

void
GrayscaleTransformation :: apply (Image & image)
{
    // Lamda for averaging the RGB values
    auto average = [](uint8_t r, uint8_t g, uint8_t b) -> uint8_t {
        uint16_t sum = r + g + b; // 16-bit to avoid overflow
        return sum / 3;
    };

    // Lamda for changing all the RGB values to the same value
    auto set_colors = [&average](Image & i, size_t row, size_t col) {
        uint8_t r = i.GetRed   (row, col);
        uint8_t g = i.GetGreen (row, col);
        uint8_t b = i.GetBlue  (row, col);
        uint8_t intensity = average(r, g, b);
        i.SetRed   (row, col, intensity);
        i.SetGreen (row, col, intensity);
        i.SetBlue  (row, col, intensity);
    };

    for (int row = 0; row < image.GetHeight(); ++row)
        for (int col = 0; col < image.GetWidth(); ++col)
            set_colors(image, row, col);
}

/*----------------------------- AdjustBrightness -----------------------------*/

AdjustBrightness :: AdjustBrightness (int offset)
: offset_{offset}
{}

void
AdjustBrightness :: apply (Image & image)
{
    // Lambda for offsetting the intensities
    auto adjust = [this](Image & i, int row, int col) {
        int r = i.GetRed   (row, col) + offset_;
        int g = i.GetGreen (row, col) + offset_;
        int b = i.GetBlue  (row, col) + offset_;
        r = r < 0 ? 0 : (r > 255 ? 255 : r);
        g = g < 0 ? 0 : (g > 255 ? 255 : g);
        b = b < 0 ? 0 : (b > 255 ? 255 : b);
        i.SetRed  (row, col, r);
        i.SetGreen(row, col, g);
        i.SetBlue (row, col, b);
    };

    for (int row = 0; row < image.GetHeight(); ++row)
        for (int col = 0; col < image.GetWidth(); ++col)
            adjust (image, row, col);
}

} // namespace Vision
