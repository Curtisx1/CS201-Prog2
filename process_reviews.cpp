// Curtis Lemke
// Program #2: Sentiment Analysis
// 10/3/2023-10/8/2023
#include "process_reviews.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "sentiment_parser.h"
#include "word_replacement.h"
#include <regex>
using namespace std;

ProcessReviews::ProcessReviews(const SentimentParser& sentimentParser, WordReplacement& wordReplacement)
    : sentimentParser(sentimentParser), wordReplacement(wordReplacement) {
}

void ProcessReviews::processReview(const string& inputFileName) {
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << inputFileName << endl;
        return;
    }

    cout << "PROCESSING FILE: " << inputFileName << endl;

    string line;
    string originalReview;
    float originalSentiment = 0.0;
    float updatedSentiment = 0.0;

    // Define a regular expression pattern to match words
    regex wordPattern(R"([a-zA-Z]+)");

    // Define the maximum line length
    const int maxLineLength = 80;

    // Open an output file stream to write the processed review
    ofstream outputFile("processed_reviews.txt");

    while (getline(inputFile, line)) {
        originalReview += line + "\n";

        istringstream iss(line);
        string word;

        while (iss >> word) {
            // Convert word to lowercase
            for (char& c : word) {
                c = tolower(c);
            }

            // Use regular expression to check if the word contains non-alphabetical characters
            if (!regex_match(word, wordPattern)) {
                continue;  // Skip words with non-alphabetical characters
            }

            float wordSentiment = sentimentParser.findSentiment(word);
            originalSentiment += wordSentiment;
        }

        // Check if the line length exceeds the maximum
        if (line.length() > maxLineLength) {
            // Split the line into multiple lines with a maximum length of 80 characters
            for (size_t i = 0; i < line.length(); i += maxLineLength) {
                string subLine = line.substr(i, maxLineLength);
                // Write the subLine to the output file
                outputFile << subLine << endl;
            }
        }
        else {
            // Write the line to the output file
            outputFile << line << endl;
        }
    }

    // Close the output file stream
    outputFile.close();

    cout << "ORIGINAL REVIEW: \n" << originalReview << endl;
    cout << "ORIGINAL SENTIMENT: " << originalSentiment << endl;

    wordReplacement.replaceWords(originalReview, originalSentiment, updatedSentiment);

    cout << "UPDATED REVIEW: \n" << originalReview << endl;
    cout << "UPDATED SENTIMENT: " << updatedSentiment << endl;

    inputFile.close();

    for (int j = 0; j < 3; ++j) {
        cout << endl;
    }
}
