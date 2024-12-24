#ifndef JUMI_ASCII_ART_APPLICATION_H
#define JUMI_ASCII_ART_APPLICATION_H
#include <vector>
#include "image.h"

class application
{
public:
    application(std::vector<image>&& images, const std::string& output_file);
    void run(int ramp);

private:
    std::vector<image> _images;
    std::string _output_file;
};

#endif

