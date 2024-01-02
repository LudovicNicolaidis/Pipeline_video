#include "detector.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

void Detector::process(VideoFrame& frame)
{
    std::ofstream outputFile("output.txt", std::ios::app);                                  // Open the file "output.txt" in append mode for writing
    if (!outputFile.is_open()) {                                                            // Check if the file opening was successful
        std::cerr << "Erreur lors de l'ouverture du fichier de sortie." << std::endl;       // If the file couldn't be opened, print an error message to the standard error stream
        return;                                                                             // Iterate through the rows of the video frame to search for a pattern using KMP algorithm
    }
                                                                                                // Iterate through the rows of the video frame to search for a pattern using KMP algorithm
    for (size_t i = 0; i < static_cast<size_t>(frame.height - pattern_height + 1); ++i) {       // Initialize variables to keep track of the current video row and pattern row
        size_t current_video_row = i;
        size_t current_pattern_row = 0;                                                         
                                                                                                // Flag to indicate whether the pattern search is finished for the current row
        bool finish = false;
                                                                                                // Vector to store the last indices where matches were found for each pattern row
        std::vector<int> tab_index = {-1, -1, -1, -1};                                          // Variable to track the maximum index in tab_index
        int base_index = -1;
                                                                                                // Continue searching for the pattern in the current row until finished
        while (!finish) {
            
            int found_index = 0;                                                                                    // Initialize the found index to 0
            std::string data = std::string(pattern[current_pattern_row]);                                           // Extract the current pattern row as a string for comparison
            size_t index = current_video_row * frame.width;                                                         // Calculate the starting index in the video frame data for the current row
            std::string s(frame.data.begin() + index, frame.data.begin() + index + frame.width);                    // Extract the relevant portion of the frame data for comparison
            base_index = (base_index == -1) ? 0 : *std::max_element(tab_index.begin(), tab_index.end());            // Update the base index to start the search at the last found index
                                                                                                                    // Output the current frame data for debugging purposes
            if (base_index == tab_index[current_pattern_row]) {
                current_pattern_row++;                                                                              // Check if the current base index matches the expected index for the pattern row
                current_video_row++;                                                                                // Move to the next pattern and video rows if a match is found
                continue;
            }
            if (KMPSearch(data, s, base_index, found_index)) {

                if (current_pattern_row == pattern_height && base_index == found_index) {                           // Check if the KMP pattern search is successful
                    outputFile << "Pattern found at index " << found_index << " and row " << i << "\n";             // Check if the entire pattern has been found in the current row and at the expected index
                    for (size_t j = 0; j < 4; ++j) {
                        size_t currentRow = i + j;
                        if (currentRow < frame.height) {                                                            // Output the part of the frame where the pattern is detected to the console
                            for (size_t k = 0; k < static_cast<size_t>(frame.width); ++k) {
                                outputFile << frame.data[currentRow * frame.width + k];
                            }
                            outputFile << "\n";
                        }
                    }
                    tab_index[0] = found_index + 1;                          // Update the tab_index to continue searching on the same row
                    current_pattern_row = 0;                                 // Reset pattern and video row indices for the next iteration
                    current_video_row = i;
                    continue;
                }

                tab_index[current_pattern_row] = found_index;                // Update the tab_index with the found index
                if (base_index != found_index) {                             // Check if the base index is different from the found index
                    if (current_pattern_row == 0) {
                        current_pattern_row++;
                        current_video_row++;
                    } else {                                                 // If it's not the first pattern row, reset both row indices to the start of the current iteration
                        current_pattern_row = 0;
                        current_video_row = i;
                    }
                } else {                                                     // If the base index is the same, increment both row indices
                    current_pattern_row++;
                    current_video_row++;
                }
            } else {                                                         // If KMP search is not successful, finish searching in the current row
                finish = true;
            }
        }
    }
}

int Detector::KMPSearch(std::string pat, std::string txt, int base_index, int& found_index)     // Function to perform pattern searching using the Knuth–Morris–Pratt algorithm
{
    size_t pattern_size = pat.length();                                                         // Get the length of the pattern
    int *lps = new int[static_cast<size_t>(pattern_size)];                                      // Create an array to store the Longest Prefix Suffix values
    size_t txt_size = txt.length();                                                             // Get the length of the text


    computeLPSArray(pat, static_cast<int>(pattern_size), lps);                                  // Compute the Longest Prefix Suffix array for the pattern

    int i = base_index;                                                                         // Initialize indices for pattern and text
    int j = 0;          

    while (static_cast<size_t>(i) < txt_size) {                                                 // Perform pattern matching
        if (pat[j] == txt[i]) {                                                                 // If characters match, increment both indices
            j++;                                                                                
            i++;
        }
        if (static_cast<size_t>(j) == pattern_size) {                                           // If the entire pattern is found, update the found_index and return 1 (success)
            found_index = i - j;
            delete[] lps;                                                                       // Deallocate memory
            return 1;
        }


        else if (static_cast<size_t>(i) < txt_size && pat[j] != txt[i]) {                       // If characters do not match
            if (j != 0)
                j = lps[j - 1];                                                                 // Move j to the previous matching position
            else    
                i = i + 1;                                                                      // Move to the next character in the text
        }
    }

    delete[] lps;                                                                               // Deallocate memory and return 0 (pattern not found)

    return 0;
}

void Detector::computeLPSArray(std::string pat, int m, int *lps)                                // Function to compute the Longest Prefix Suffix array for the pattern
{
    int len = 0;
    int i = 1;

    lps[0] = 0;                                                                                 // The first value of the LPS array is always 0

    while (i < m) {
        if (pat[i] == pat[len]) {                                                               // Compute the LPS array values for the pattern
            len++;                                                                              // If characters match, update LPS value and increment both indices
            lps[i++] = len;
        } else
        {
            if (len != 0) {                                                                     // If characters do not match and there was a previous match, update len

                len = lps[len - 1];

            } else                                                                              // If characters do not match and there was no previous match, set LPS value to 0
            {
                lps[i++] = 0;
            }
        }
    }
}
