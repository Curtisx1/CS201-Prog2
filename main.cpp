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
        SentimentParser sentimentParser("sentiment.txt");
        WordReplacement wordReplacement(sentimentParser);
        ProcessReviews processReviews(sentimentParser, wordReplacement);

        // Get the current directory where the program is located
        string currentDirectory = fs::current_path().string();
        cout << "Current Directory: " << currentDirectory << endl;

        // Iterate through all files in the current directory
        for (const auto& entry : fs::directory_iterator(currentDirectory)) {
            string inputFileName = entry.path().string();

            // Compare the full file path with "sentiment.txt" to ignore it
            if (inputFileName == currentDirectory + "\\sentiment.txt") {
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
    catch (const filesystem::filesystem_error& ex) {
        cerr << "Filesystem Error: " << ex.what() << endl;
    }
    return 0;
}
