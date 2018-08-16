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
Grayscale :: apply (Image & image)
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

/*------------------------------- InvertColors -------------------------------*/

void
InvertColors :: apply (Image & image)
{
    auto set_colors = [&](Image & i, size_t row, size_t col) {
        uint8_t const max = 255;
        uint8_t r = max - i.GetRed   (row, col);
        uint8_t g = max - i.GetGreen (row, col);
        uint8_t b = max - i.GetBlue  (row, col);
        i.SetRed   (row, col, r);
        i.SetGreen (row, col, g);
        i.SetBlue  (row, col, b);
    };

    for (int row = 0; row < image.GetHeight(); ++row)
        for (int col = 0; col < image.GetWidth(); ++col)
            set_colors(image, row, col);
}

/*----------------------- Statistical Transformations ------------------------*/

Statistical :: Statistical (size_t boxsize)
: boxsize_{boxsize}
{}

Statistical :: Box :: Box
(size_t top, size_t bottom, size_t left, size_t right)
: top_{top}, bottom_{bottom}, left_{left}, right_{right}
{
    assert(bottom_ > top_);
    assert(right_ > left_);
}

bool
Statistical :: Box :: Contains (size_t row, size_t col) const
{
    bool valid_row = (row >= bottom_ && row <= top_);
    bool valid_col = (col >= left_ && col <= right_);
    return valid_row && valid_col;
}

std::vector<Statistical::Box>
Statistical :: GetBoxes (Image const & image) const
{
    size_t img_height = image.GetHeight();
    size_t img_width  = image.GetWidth();
    std::vector<Box> boxes;
    for (size_t i = 0; i < img_height; i += boxsize_) {
        size_t bottom = i + boxsize_ - 1;
        bottom = bottom < img_height ? bottom : img_height - 1;
        for (size_t j = 0; j < img_width; j += boxsize_) {
            size_t right = j + boxsize_ - 1;
            right = right < img_width ? right : img_width - 1;
            boxes.emplace_back(i, bottom, j, right);
        }
    }
    return boxes;
}

Average :: Average (size_t boxsize)
: Statistical(boxsize)
{}

void
Average :: apply (Image & image)
{
    auto boxes = GetBoxes(image);

    std::vector<uint8_t> red_averages;
    std::vector<uint8_t> green_averages;
    std::vector<uint8_t> blue_averages;

    // Calculate average RGB intensities for each box
    for (auto const & box : boxes) {
        int r = 0, g = 0, b = 0;
        for (size_t i = box.Top(); i <= box.Bottom(); ++i) {
            for (size_t j = box.Left(); j <= box.Right(); ++j) {
                r += image.GetRed  (i, j);
                g += image.GetGreen(i, j);
                b += image.GetBlue (i, j);
            }
        }
        red_averages.push_back  (r / box.Size());
        green_averages.push_back(g / box.Size());
        blue_averages.push_back (b / box.Size());
    }

    // Set the RGB intensities in original image
    for (int index = 0; index < boxes.size(); ++index) {
        auto & box = boxes.at(index);
        for (size_t i = box.Top(); i <= box.Bottom(); ++i)
            for (size_t j = box.Left(); j <= box.Right(); ++j) {
                image.SetRed  (i, j, red_averages.at  (index));
                image.SetGreen(i, j, green_averages.at(index));
                image.SetBlue (i, j, blue_averages.at (index));
            }
    }
}

StandardDeviation :: StandardDeviation (size_t boxsize)
: Statistical(boxsize)
{}

void
StandardDeviation :: apply (Image & image)
{
    auto boxes = GetBoxes(image);

    // Calculate average RGB intensities for each box
    std::vector<uint8_t> red_averages;
    std::vector<uint8_t> green_averages;
    std::vector<uint8_t> blue_averages;
    for (auto const & box : boxes) {
        int r = 0, g = 0, b = 0;
        for (size_t i = box.Top(); i <= box.Bottom(); ++i) {
            for (size_t j = box.Left(); j <= box.Right(); ++j) {
                r += image.GetRed  (i, j);
                g += image.GetGreen(i, j);
                b += image.GetBlue (i, j);
            }
        }
        red_averages.push_back  (r / box.Size());
        green_averages.push_back(g / box.Size());
        blue_averages.push_back (b / box.Size());
    }

    // Calculate the standard deviation of RGB intensities for each box
    std::vector<uint8_t> red_stdevs;
    std::vector<uint8_t> green_stdevs;
    std::vector<uint8_t> blue_stdevs;
    for (int index = 0; index < boxes.size(); ++index) {
        auto & box = boxes.at(index);
        int r = 0, g = 0, b = 0;
        for (size_t i = box.Top(); i <= box.Bottom(); ++i) {
            for (size_t j = box.Left(); j <= box.Right(); ++j) {
                r += pow(image.GetRed  (i, j) - red_averages.at(index),   2);
                g += pow(image.GetGreen(i, j) - green_averages.at(index), 2);
                b += pow(image.GetBlue (i, j) - blue_averages.at(index),  2);
            }
        }
        r /= box.Size() - 1;
        g /= box.Size() - 1;
        b /= box.Size() - 1;
        red_stdevs.push_back  (sqrt(r));
        green_stdevs.push_back(sqrt(g));
        blue_stdevs.push_back (sqrt(b));
    }

    // Set the RGB intensities in original image
    for (int index = 0; index < boxes.size(); ++index) {
        auto & box = boxes.at(index);
        for (size_t i = box.Top(); i <= box.Bottom(); ++i)
            for (size_t j = box.Left(); j <= box.Right(); ++j) {
                image.SetRed  (i, j, red_stdevs.at  (index));
                image.SetGreen(i, j, green_stdevs.at(index));
                image.SetBlue (i, j, blue_stdevs.at (index));
            }
    }
}

} // namespace Vision
