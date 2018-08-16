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
    auto set_colors = [](Image & i, size_t row, size_t col, uint8_t intensity) {
        i.SetRed   (row, col, intensity);
        i.SetGreen (row, col, intensity);
        i.SetBlue  (row, col, intensity);
    };

    for (int row = 0; row < image.GetHeight(); ++row)
        for (int col = 0; col < image.GetWidth(); ++col) {
            uint8_t r = image.GetRed   (row, col);
            uint8_t g = image.GetGreen (row, col);
            uint8_t b = image.GetBlue  (row, col);
            set_colors(image, row, col, average(r, g, b));
        }
}

} // namespace Vision
