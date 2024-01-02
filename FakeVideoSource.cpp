#include "FakeVideoSource.hpp"
#include <iostream>

FakeVideoSource::FakeVideoSource(unsigned int w, unsigned int h, unsigned int rate)     // Constructor for the FakeVideoSource class, initializes width, height, frameRate, and sets isRunning to false
    : width(w), height(h), frameRate(rate), isRunning(false) {
    std::srand(std::time(0)); // Seed for random values                                 // Seed for random values
}

void FakeVideoSource::start() {                                                         // Start function for the FakeVideoSource, initiates frame generation and pushes frames downstream
    isRunning = true;
    while (isRunning) {
        generateFrame();                                                                // Generate a new video frame
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frameRate));
    }
}

void FakeVideoSource::generateFrame() {                                                 // Function to generate a random VideoFrame with '0' or '1' pixels and push it downstream
    VideoFrame frame(width, height);                                                    // Create a VideoFrame object with specified width and height

    for (char& pixel : frame.data) {                                                    // Populate each pixel in the frame with a randomly chosen '0' or '1'
        pixel = (std::rand() % 2 == 0) ? '0' : '1';                                     // Randomly choose '0' or '1'
    }
    processAndPushDownstream(frame);                                                    // Push the generated frame downstream in the processing pipeline
}

void FakeVideoSource::process(VideoFrame& frame) {
    // Optional: Implement specific processing logic for the fake video source
    // This function is overridden from the base class PipelineElement
}
