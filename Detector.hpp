// detector.hpp

#pragma once

#include "pipelineElement.hpp"
#include <string>

class Detector : public PipelineElement {
private:
    // static const int pattern_width = 4;
    // static const int pattern_height = 4;
    // char pattern[pattern_height][pattern_width] = {"101",
    //                                                "111",
    //                                                "010",
    //                                                "101"};
    // Comment above lines (10-15) and uncomment following (17-20) to test the code with a smaller pattern.
    static const int pattern_width = 4;
    static const int pattern_height = 2;
    char pattern[pattern_height][pattern_width] = {"101",
                                                   "111"};
    int KMPSearch(std::string pat, std::string txt, int base_index, int& found_index);
    void computeLPSArray(std::string pat, int M, int *lps);

public:
    void process(VideoFrame& frame) override;
    virtual ~Detector(){}
};
