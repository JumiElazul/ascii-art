#ifndef JUMI_ASCII_ART_APPLICATION_H
#define JUMI_ASCII_ART_APPLICATION_H
#include <vector>
#include "image_loader.h"

class application
{
public:
    application(std::vector<image>&& images);

private:
    std::vector<image> _images;
};

#endif

