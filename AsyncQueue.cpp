#include "AsyncQueue.hpp"
#include <iostream>

// Constructor initializes the AsyncQueue with the specified maximum number of frames.
AsyncQueue::AsyncQueue(size_t maxFrames) : maxFrames(maxFrames), stopProcessing(false) {
    // Start the processing thread upon construction.
    startProcessingThread();
}

// Destructor signals the processing thread to stop and waits for its completion.
AsyncQueue::~AsyncQueue() {
    // Signal the processing thread to stop.
    stopProcessing = true;

    // Notify the processing thread to wake up and check the stop condition.
    queueCV.notify_one();

    // Wait for the processing thread to finish its execution.
    if (processingThread.joinable()) {
        processingThread.join();
    }
}

// Start the processing thread.
void AsyncQueue::startProcessingThread() {
    processingThread = std::thread(&AsyncQueue::processingLoop, this);
}

// Main processing loop for the asynchronous queue.
void AsyncQueue::processingLoop() {
    while (!stopProcessing) {
        std::unique_lock<std::mutex> lock(queueMutex);

        // Wait for either new frames or a signal to stop processing.
        queueCV.wait(lock, [this] { return !frameQueue.empty() || stopProcessing; });

        if (!frameQueue.empty()) {
            // Retrieve the front frame from the queue.
            VideoFrame frame = frameQueue.front();
            frameQueue.pop_front();
            lock.unlock();

            // Process the frame and push it downstream to connected elements.
            processAndPushDownstream(frame);
        }
    }
}

// Process function for adding a new frame to the asynchronous queue.
void AsyncQueue::process(VideoFrame& frame) {
    std::lock_guard<std::mutex> lock(queueMutex);

    // Drop the oldest frame if the maximum number of frames is reached.
    if (frameQueue.size() >= maxFrames) {
        frameQueue.pop_front();
    }

    // Add the new frame to the queue.
    frameQueue.push_back(frame);

    // Notify the processing thread to wake up and process the new frame.
    queueCV.notify_one();
}
