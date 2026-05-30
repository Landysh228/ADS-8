// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>
#include <chrono>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    std::cout << "=== Word Frequency Analysis ===" << std::endl;
    std::cout << "Analyzing: War and Peace by Leo Tolstoy" << std::endl;
    std::cout << "=========================================\n" << std::endl;
    
    BST<std::string> wordTree;
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::cout << "Loading and analyzing the text..." << std::endl;
    makeTree(wordTree, "src/war_peace.txt");
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    if (wordTree.size() == 0) {
        std::cout << "Failed to load words from file!" << std::endl;
        std::cout << "Please make sure the file 'src/war_peace.txt' exists." << std::endl;
        return 1;
    }
    
    std::cout << "\nAnalysis completed successfully!" << std::endl;
    std::cout << "Total unique words: " << wordTree.size() << std::endl;
    std::cout << "Tree depth: " << wordTree.depth() << std::endl;
    std::cout << "Processing time: " << duration.count() << " ms" << std::endl;
    
    std::cout << "\n=== Testing search functionality ===" << std::endl;
    std::string testWords[] = {"the", "war", "peace", "and", "tolstoy", "nonexistent"};
    for (const auto& testWord : testWords) {
        if (wordTree.search(testWord)) {
            std::cout << "Found: '" << testWord << "'" << std::endl;
        } else {
            std::cout << "Not found: '" << testWord << "'" << std::endl;
        }
    }
    
    std::cout << "\n" << std::endl;
    printFreq(wordTree);
    
    return 0;
}
