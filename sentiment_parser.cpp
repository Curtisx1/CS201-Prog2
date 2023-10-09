// Curtis Lemke
// Program #2: Sentiment Analysis
// 10/3/2023-10/8/2023
#include "sentiment_parser.h"
#include <fstream>
#include <sstream>
using namespace std;

SentimentParser::SentimentParser(const string& filename) {
    // Implement the constructor to read and parse 'sentiment.txt'
    ifstream file(filename);
    if (!file.is_open()) {
        // Handle file open error
        return;
    }

    // Read and parse the file to populate sentiments, positiveWords, and negativeWords vectors
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string word;
        float sentimentValue;

        if (getline(iss, word, ',') && iss >> sentimentValue) {
            WordSentiment ws;
            ws.word = word;
            ws.sentiment = sentimentValue;
            sentiments.push_back(ws);

            // Checking if the value is higher or lower than 1
            if (sentimentValue > 1.00) {
                positiveWords.push_back(word);
            }
            else if (sentimentValue < -1.00) {
                negativeWords.push_back(word);
            }
        }
    }

    file.close();
}

vector<WordSentiment> SentimentParser::getSentiments() const {
    return sentiments;
}

vector<string> SentimentParser::getPositiveWords() const {
    return positiveWords;
}

vector<string> SentimentParser::getNegativeWords() const {
    return negativeWords;
}

// Implement the findSentiment function
float SentimentParser::findSentiment(const string& word) const {
    for (const WordSentiment& ws : sentiments) {
        if (ws.word == word) {
            return ws.sentiment;
        }
    }
    // Return a default value. In this case I chose 0.
    return 0.0;
}