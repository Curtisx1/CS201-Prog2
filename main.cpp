// Curtis Lemke
// Program #2: Sentiment Analysis
// 10/3/2023-10/8/2023

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "sentiment_parser.h"
#include "word_replacement.h"
#include "process_reviews.h"
using namespace std;
namespace fs = filesystem;

int main() {
    try {
        // This passes the sentiment file to the parser so it can be used
        SentimentParser sentimentParser("sentiment.txt");
        WordReplacement wordReplacement(sentimentParser);
        ProcessReviews processReviews(sentimentParser, wordReplacement);

        // Get the current directory where the program is located. 
        // The reason for this is because I could not get VS to find the review files without it.
        string currentDirectory = fs::current_path().string();
        cout << "Current Directory: " << currentDirectory << endl;

        // Iterate through all files in the current directory
        for (const auto& entry : fs::directory_iterator(currentDirectory)) {
            string inputFileName = entry.path().string();

            // Compare the full file path with "sentiment.txt" to ignore it. Had a lot of issues getting this to work.
            if (inputFileName == currentDirectory + "\\sentiment.txt") {
                continue;
            }
            // Same for the temp file used to process the reviews
            if (inputFileName == currentDirectory + "\\processed_reviews.txt") {
                continue;
            }

            if (entry.is_regular_file() && inputFileName.substr(inputFileName.find_last_of(".") + 1) == "txt") {
                ifstream inputFile(inputFileName);
                if (!inputFile.is_open()) {
                    cerr << "Error: Could not open file " << inputFileName << endl;
                    continue;
                }
                // Process the review using the ProcessReviews class
                processReviews.processReview(inputFileName);
                inputFile.close(); // Close the ifstream after processing
            }
        }
    }
    // Added this to help debug when creating the program.
    catch (const filesystem::filesystem_error& ex) {
        cerr << "Filesystem Error: " << ex.what() << endl;
    }
    return 0;
}