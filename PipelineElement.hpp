#pragma once

#include "VideoFrame.hpp"
#include <vector>

class PipelineElement {
public:
    virtual void process(VideoFrame& frame) = 0;
    void link(PipelineElement* downstream);
    void processAndPushDownstream(VideoFrame& frame);

protected:
    std::vector<PipelineElement*> downstreamElements;
};
