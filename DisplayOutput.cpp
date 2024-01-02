#include "DisplayOutput.hpp"
#include <iostream>

void DisplayOutput::process(VideoFrame& frame) {
    // Clear and reset cursor
    std::cout << "\033[2J\033[H";

    // Output each pixel value as part of a block
    for (unsigned int i = 0; i < frame.height; ++i) {
        for (unsigned int j = 0; j < frame.width; ++j) {
            std::cout << frame.data[i * frame.width + j];
        }
        std::cout << "\n";
    }

    // Flush to ensure immediate display
    std::cout << std::flush;
}
