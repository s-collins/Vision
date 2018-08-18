#ifndef VISION_FILE_MANAGER_HPP
#define VISION_FILE_MANAGER_HPP

#include "Vision/Image.hpp"

namespace Vision {

class FileManager
{
public:
    Image* OpenImage (std::string path);
    void   SaveImage (std::string path, Image const &);

protected:
    FileManager * instance_;
};

} // namespace Vision

#endif // VISION_FILE_MANAGER_HPP