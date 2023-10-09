// Curtis Lemke
// Program #2: Sentiment Analysis
// 10/3/2023-10/8/2023

#include <iostream>
#include <sstream>
#include <vector>
#include "word_replacement.h"
#include <random>
#include <iomanip>

using namespace std;

WordReplacement::WordReplacement(const SentimentParser& sentimentParser) : sentimentParser(sentimentParser) {
    // Initialize random number generator
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

    // Prepare data for output formatting
    vector<pair<string, string>> replacements;  // Store original and replacement words
    float totalSentimentChange = 0.0;

    // Loop through the words in the review
    for (string& word : words) {
        // Convert word to lowercase and remove punctuation
        string originalWord = word;  // Store the original word
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

                // Replace the word in the words vector and update sentiment
                updatedSentiment -= wordSentiment;  // Subtract the negative sentiment
                for (char& c : replacementWord) {
                    c = tolower(c);
                }
                word = replacementWord;
                updatedSentiment += sentimentParser.findSentiment(replacementWord);  // Add the positive sentiment
                ++numWordsReplaced;

                // Store original and replacement words for output
                replacements.push_back(make_pair(originalWord, replacementWord));
                totalSentimentChange += sentimentParser.findSentiment(replacementWord) - wordSentiment;
            }
        }
    }

    // Join the words back into the review
    review = "";
    for (const string& word : words) {
        review += word + " ";
    }

    // Output the word replacements and sentiment changes
    cout << "WORDS UPDATED TO BE MORE POSITIVE:" << endl;
    cout << setw(20) << left << "Original" << setw(20) << "Replacement" << setw(10) << "Change" << endl;
    cout << fixed << setprecision(2);
    for (const auto& replacement : replacements) {
        cout << setw(20) << left << replacement.first << setw(20) << replacement.second
            << setw(10) << sentimentParser.findSentiment(replacement.second) - sentimentParser.findSentiment(replacement.first) << endl;
    }

    // Output the totals
    cout << "TOTALS:" << endl;
    cout << setw(20) << "-" << setw(20) << numWordsReplaced << setw(10) << totalSentimentChange << endl;

    // Print the number of words replaced
    cout << "Words replaced: " << numWordsReplaced << endl;
}
