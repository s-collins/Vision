#ifndef VISION_FILE_MANAGER_HPP
#define VISION_FILE_MANAGER_HPP

#include "Vision/Image.hpp"

namespace Vision {

/*----------------------------- FileManager Base -----------------------------*/

class FileManager
{
public:
    virtual Image* OpenImage (std::string)                = 0;
    virtual void   SaveImage (std::string, Image const &) = 0;
};

/*---------------------------- OpenCV FileManager ----------------------------*/

class OpenCVFileManager : public FileManager
{
public:
    Image* OpenImage (std::string)                override;
    void   SaveImage (std::string, Image const &) override;
};

} // namespace Vision

#endif // VISION_FILE_MANAGER_HPP
