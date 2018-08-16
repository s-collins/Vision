/*******************************************************************************
COPYRIGHT (C) 2018 University of Akron Robotics Team. All rights reserved.
File Name : Editor.cpp
Author    : Sean Collins
Email     : sgc29@zips.uakron.edu
Date      : 16 August 2018
Purpose   : Implements the Editors.
*******************************************************************************/
#include "Vision/Editor.hpp"
#include "Vision/Transformation.hpp"

namespace Vision {

/*------------------------------- Editor Base --------------------------------*/

Editor :: ~Editor ()
{
    for (auto & p_transform : transforms_)
        delete p_transform;
}

void
Editor :: add (Transformation * p_transform)
{
    transforms_.push_back(p_transform);
}

void
Editor :: edit (Image & image)
{
    for (auto & p_transform : transforms_)
        p_transform->apply(image);
}

/*------------------------------ OpenCV Editor -------------------------------*/

void
OpenCVEditor :: edit (Image & image)
{
    Editor::edit(image);
    // TODO: Add special transformations somewhere in this method...
}

} // namespace Vision
