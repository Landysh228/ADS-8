#include "bst.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream srcFile(filename);
    
    if (!srcFile.is_open()) {
        std::cout << "File error!" << std::endl;
        return;
    }
    
    std::string currentWord = "";
    int currentChar = srcFile.get();
    
    while (currentChar != EOF) {
        if (std::isalpha(currentChar) && static_cast<char>(currentChar) >= 'A' && static_cast<char>(currentChar) <= 'z') {
            currentWord += static_cast<char>(std::tolower(currentChar));
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord.clear();
            }
        }
        currentChar = srcFile.get();
    }
    
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
    
    srcFile.close();
}

bool compareByFrequency(const BST<std::string>::Pair& a, const BST<std::string>::Pair& b) {
    return a.count > b.count;
}

void printFreq(BST<std::string>& tree) {
    BST<std::string>::Pair* sortedWordsArray = nullptr;
    int arraySize = tree.getSortedArray(sortedWordsArray);
    
    if (arraySize == 0) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }
    
    BST<std::string>::Pair* freqSortedArray = new BST<std::string>::Pair[arraySize];
    for (int i = 0; i < arraySize; i++) {
        freqSortedArray[i] = sortedWordsArray[i];
    }
    
    std::sort(freqSortedArray, freqSortedArray + arraySize, compareByFrequency);
    
    std::ofstream reportFile("result/freq.txt");
    if (!reportFile.is_open()) {
        std::cout << "Error creating result file!" << std::endl;
        delete[] sortedWordsArray;
        delete[] freqSortedArray;
        return;
    }
    
    std::cout << "\n=== WORD FREQUENCY ANALYSIS ===" << std::endl;
    std::cout << "Total unique words: " << arraySize << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "\nWords sorted by frequency (descending):" << std::endl;
    std::cout << "=================================" << std::endl;
    
    reportFile << "=== WORD FREQUENCY ANALYSIS ===" << std::endl;
    reportFile << "Total unique words: " << arraySize << std::endl;
    reportFile << "Tree depth: " << tree.depth() << std::endl;
    reportFile << "\nWords sorted by frequency (descending):" << std::endl;
    reportFile << "=================================" << std::endl;
    
    int displayLimit = std::min(20, arraySize);
    for (int index = 0; index < displayLimit; ++index) {
        std::cout << freqSortedArray[index].word << ": " << freqSortedArray[index].count << std::endl;
        reportFile << freqSortedArray[index].word << ": " << freqSortedArray[index].count << std::endl;
    }
    
    if (arraySize > 20) {
        std::cout << "... and " << (arraySize - 20) << " more words" << std::endl;
        reportFile << "... and " << (arraySize - 20) << " more words" << std::endl;
    }
    
    reportFile << "\n=== WORDS IN ALPHABETICAL ORDER ===" << std::endl;
    for (int index = 0; index < arraySize; ++index) {
        reportFile << sortedWordsArray[index].word << ": " << sortedWordsArray[index].count << std::endl;
    }
    
    reportFile.close();
    
    delete[] sortedWordsArray;
    delete[] freqSortedArray;
    
    std::cout << "\nResults saved to result/freq.txt" << std::endl;
}
