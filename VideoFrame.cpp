#include "VideoFrame.hpp"

VideoFrame::VideoFrame(unsigned int w, unsigned int h) : width(w), height(h) {
    data.resize(width * height);
}
