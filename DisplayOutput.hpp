#pragma once

#include <iostream>
#include "PipelineElement.hpp"

class DisplayOutput : public PipelineElement {
public:
    virtual void process(VideoFrame& frame) override;
};
