// Curtis Lemke
// Program #2: Sentiment Analysis
// 10/3/2023-10/8/2023
#include <iostream>
#include <sstream>
#include <vector>
#include "word_replacement.h"
#include <random>
#include <algorithm>
using namespace std;

WordReplacement::WordReplacement(const SentimentParser& sentimentParser) : sentimentParser(sentimentParser) {
    // Initialize random number generator
    // Found the mt19937 from here: https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/
    random_device rd;
    randomGenerator = mt19937(rd());
}

void WordReplacement::replaceWords(string& review, float& originalSentiment, float& updatedSentiment) {
    // Split the review into words
    istringstream iss(review);
    vector<string> words;
    string word;
    while (iss >> word) {
        words.push_back(word);
    }

    // Initialize variables to track changes and sentiment scores
    int numWordsReplaced = 0;
    originalSentiment = 0.0;
    updatedSentiment = 0.0;

    // Loop through the words in the review
    for (string& word : words) {
        // Convert word to lowercase and remove punctuation
        // For some reason I cannot get this to work properly with review5a.txt
        for (char& c : word) {
            c = tolower(c);
        }
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

        // Find the word in the sentiment data
        float wordSentiment = 0.0;
        for (const WordSentiment& ws : sentimentParser.getSentiments()) {
            if (ws.word == word) {
                wordSentiment = ws.sentiment;
                break;  // Found the word, no need to continue searching
            }
        }

        // Update sentiment scores
        originalSentiment += wordSentiment;
        updatedSentiment += wordSentiment;

        // Check if the word sentiment is negative enough for replacement
        if (wordSentiment < -1.0) {
            // Randomly select a positive replacement
            vector<string> positiveWords = sentimentParser.getPositiveWords();
            if (!positiveWords.empty()) {
                uniform_int_distribution<int> distribution(0, positiveWords.size() - 1);
                int randomIndex = distribution(randomGenerator);
                string replacementWord = positiveWords[randomIndex];

                // Replace the word and update sentiment
                updatedSentiment -= wordSentiment;  // Subtract the negative sentiment
                for (char& c : replacementWord) {
                    c = tolower(c);
                }
                word = replacementWord;
                updatedSentiment += sentimentParser.getSentiments()[randomIndex].sentiment;  // Add the positive sentiment
                ++numWordsReplaced;
            }
        }
    }

    // Join the words back into the review
    review = "";
    for (const string& word : words) {
        review += word + " ";
    }

    // Print the number of words replaced
    cout << "Words replaced: " << numWordsReplaced << endl;
}
