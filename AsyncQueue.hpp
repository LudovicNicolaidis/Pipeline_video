#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "PipelineElement.hpp"

class AsyncQueue : public PipelineElement {
public:
    AsyncQueue(size_t maxFrames);
    ~AsyncQueue();

    void process(VideoFrame& frame) override;

private:
    std::deque<VideoFrame> frameQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    size_t maxFrames;
    std::thread processingThread;
    bool stopProcessing;

    void startProcessingThread();
    void processingLoop();
};
