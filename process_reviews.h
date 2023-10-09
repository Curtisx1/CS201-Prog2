#pragma once
#ifndef PROCESS_REVIEWS_H
#define PROCESS_REVIEWS_H

#include "sentiment_parser.h"
#include "word_replacement.h"
#include <string> // Add this line to include the <string> header

class ProcessReviews {
public:
    // Constructor
    ProcessReviews(const SentimentParser& sentimentParser, WordReplacement& wordReplacement);

    // Function to process a review
    void processReview(const std::string& inputFileName); // Use 'std::string' instead of 'string'

private:
    const SentimentParser& sentimentParser;
    WordReplacement& wordReplacement;
};

#endif  // PROCESS_REVIEWS_H
