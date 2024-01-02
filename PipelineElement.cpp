#include "PipelineElement.hpp"

// Link the current pipeline element to a downstream element.
void PipelineElement::link(PipelineElement* downstream) {
    downstreamElements.push_back(downstream);
}

// Process the video frame and push it downstream to connected elements.
void PipelineElement::processAndPushDownstream(VideoFrame& frame) {
    // Process the video frame using the specific implementation in derived classes.
    process(frame);

    // Push the processed video frame downstream to connected elements.
    for (auto& downstream : downstreamElements) {
        downstream->processAndPushDownstream(frame);
    }
}

// Example function representing a placeholder for custom processing logic.
void MyFunction(VideoFrame& frame) {
    // Unused parameter to avoid compilation warnings.
    (void)frame;
}
