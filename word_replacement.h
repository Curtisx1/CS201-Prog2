#ifndef WORD_REPLACEMENT_H
#define WORD_REPLACEMENT_H

#include "sentiment_parser.h"
#include <random>
#include <vector>
#include <string>  // Add this line to include the <string> header

class WordReplacement {
public:
    // Constructor
    WordReplacement(const SentimentParser& sentimentParser);

    // Function to replace words and update sentiments
    void replaceWords(std::string& review, float& originalSentiment, float& updatedSentiment);  // Use 'std::string' instead of 'string'

private:
    const SentimentParser& sentimentParser;  // Reference to SentimentParser

    // Random number generator for word replacement
    std::mt19937 randomGenerator;  // Use 'std::mt19937' instead of 'mt19937'
};

#endif  // WORD_REPLACEMENT_H
