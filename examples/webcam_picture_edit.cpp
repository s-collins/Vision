#include "Vision/Camera.hpp"
#include "Vision/Display.hpp"
#include "Vision/Editor.hpp"
#include "Vision/Factory.hpp"
#include "Vision/Image.hpp"
#include "Vision/Transformation.hpp"
#include "Vision/FileManager.hpp"
#include <memory>

int main ()
{
    using namespace Vision;
    using namespace std;

    // Create the factory
    unique_ptr<Factory> factory = make_unique<OpenCVFactory>();

    // Make the camera
    // (0 -> built-in camera; 1 -> auxiliary camera)
    unique_ptr<Camera> camera { factory->MakeCamera(Camera::BUILT_IN_CAM) };

    // Make the display
    unique_ptr<Display> display { factory->MakeDisplay("Webcam Example") };

    // Take a picture
    unique_ptr<Image> image { camera->TakePicture() };

    // Create an editor and add some transformations
    unique_ptr<Editor> editor { factory->MakeEditor() };
    //editor->add(new Average(10));
    //editor->add(new StandardDeviation (8));
    editor->add(new Grayscale);
    editor->add(new AdjustBrightness(128));
    editor->add(new AdjustContrast(2));
    editor->add(new AdjustBrightness(-128));
    //editor->add(new Threshold (15));
    //editor->add(new InvertColors);
    editor->edit(*image);

    // Display the picture
    display->show(*image);

    FileManager files;
    files.SaveImage("bin/Test.png", *image);
}