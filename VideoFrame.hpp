#pragma once

#include <vector>

struct VideoFrame {
    unsigned int width;
    unsigned int height;
    std::vector<char> data;

    VideoFrame(unsigned int w, unsigned int h);
};
