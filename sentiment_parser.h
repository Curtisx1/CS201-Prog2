#ifndef SENTIMENT_PARSER_H
#define SENTIMENT_PARSER_H

#include <vector>
#include <string>

struct WordSentiment {
    std::string word;  // Use 'std::string' instead of 'string'
    float sentiment;
};

class SentimentParser {
public:
    SentimentParser(const std::string& filename);
    std::vector<WordSentiment> getSentiments() const;
    std::vector<std::string> getPositiveWords() const;
    std::vector<std::string> getNegativeWords() const;

    // Declare the findSentiment function
    float findSentiment(const std::string& word) const;

private:
    std::vector<WordSentiment> sentiments;
    std::vector<std::string> positiveWords;
    std::vector<std::string> negativeWords;
};

#endif
