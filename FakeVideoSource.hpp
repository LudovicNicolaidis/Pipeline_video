// FakeVideoSource.hpp
#pragma once

#include "PipelineElement.hpp"  // Include the base class header
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

class FakeVideoSource : public PipelineElement {
private:
    unsigned int width;
    unsigned int height;
    unsigned int frameRate;
    bool isRunning;

public:
    FakeVideoSource(unsigned int w, unsigned int h, unsigned int rate);
    void start();
    void generateFrame();
    virtual void process(VideoFrame& frame) override;
};
