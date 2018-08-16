#include "Vision/Camera.hpp"
#include "Vision/Display.hpp"
#include "Vision/Editor.hpp"
#include "Vision/Factory.hpp"
#include "Vision/Image.hpp"
#include "Vision/Transformation.hpp"
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
    editor->add(new AdjustBrightness (-100));
    editor->add(new GrayscaleTransformation);
    editor->edit(*image);

    // Display the picture
    display->show(*image);
}