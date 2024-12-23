#include "application.h"
#include "image_loader.h"
#include <vector>

application::application(std::vector<image>&& images)
    : _images(std::move(images))
{

}
