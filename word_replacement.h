#ifndef WORD_REPLACEMENT_H
#define WORD_REPLACEMENT_H

#include "sentiment_parser.h"
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class WordReplacement {
public:
    // Constructor
    WordReplacement(const SentimentParser& sentimentParser);

    // Function to replace words and update sentiments
    void replaceWords(string& review, float& originalSentiment, float& updatedSentiment);

private:
    const SentimentParser& sentimentParser;  // Reference to SentimentParser

    // Random number generator for word replacement
    mt19937 randomGenerator; 
};

#endif  // WORD_REPLACEMENT_H
