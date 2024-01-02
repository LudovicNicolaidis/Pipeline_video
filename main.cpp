//Authors : Ludovic Nicolaids, Romain Piaumier, Maxime Courgeau


#include "FakeVideoSource.hpp"
#include "AsyncQueue.hpp"
#include "DisplayOutput.hpp"
#include "Detector.hpp"
// To end the frame generator, press ctrl + c in the terminal.
// Notes : The program works, i.e it detects the pattern in the frame and write the image in the output.txt. Tried with small patterns (see detector.hpp), width = 3, height = 4, frameRate = 1, maxFrames = 1.
// Maybe wait 20 seconds before seeing results in output.txt
// The frameRate defined line 15 worked before implementing AsyncQueue.
int main() {
    unsigned int width, height, frameRate;
    std::cout << "Enter width: ";
    std::cin >> width;
    std::cout << "Enter height: ";
    std::cin >> height;
    std::cout << "Enter frame rate: ";
    std::cin >> frameRate;

    size_t maxFrames;
    std::cout << "Enter maxFrames for AsyncQueue: ";
    std::cin >> maxFrames;

    // Instantiate elements
    FakeVideoSource source(width, height, frameRate);
    AsyncQueue asyncQueue(maxFrames); // maxFrames doesn't work, it will continue indefinetely
    DisplayOutput display;
    Detector detector;

    // The printing in AsynQueue might not work (sometimes yes sometimes no, so if it is the case, you can uncomment lines 32 to 41 and comment lines 45 to 50)
    // FakeVideoSource source(width, height, frameRate);
    // DisplayOutput display;
    // Detector detector;

    // source.link(&detector);  // Link the source to the detector

    // detector.link(&display);  // Link the detector to the display

    // // Run the pipeline by starting the video source
    // source.start();


    // Link the elements in the pipeline
    source.link(&asyncQueue);  // Link the source to the asyncQueue
    asyncQueue.link(&detector); // Link the asyncQueue to the detector
    detector.link(&display);    // Link the detector to the display

    // Run the pipeline by starting the video source
    source.start();

    // Allow some time for asynchronous processing to complete (in a real scenario, we might use proper synchronization mechanisms)
    std::this_thread::sleep_for(std::chrono::seconds(10));

}
