#ifndef SENTIMENT_PARSER_H
#define SENTIMENT_PARSER_H

#include <vector>
#include <string>
using namespace std;
struct WordSentiment {
    string word;
    float sentiment;
};

class SentimentParser {
public:
    SentimentParser(const string& filename);
    vector<WordSentiment> getSentiments() const;
    vector<string> getPositiveWords() const;
    vector<string> getNegativeWords() const;

    // Declare the findSentiment function
    float findSentiment(const string& word) const;

private:
    vector<WordSentiment> sentiments;
    vector<string> positiveWords;
    vector<string> negativeWords;
};

#endif
