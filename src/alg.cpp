#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <cctype>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream srcFile(filename);

    if (!srcFile.is_open()) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string currentWord = "";
    int currentChar = srcFile.get();

    while (currentChar != EOF) {
        if (std::isalpha(currentChar)) {
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

void printFreq(BST<std::string>& tree) {
    BST<std::string>::Pair* sortedWordsArray = nullptr;
    int arraySize = tree.getSortedArray(sortedWordsArray);

    std::ofstream reportFile("result/freq.txt");
    if (!reportFile.is_open()) {
        std::cout << "Error creating result file!" << std::endl;
        if (sortedWordsArray != nullptr) {
            delete[] sortedWordsArray;
        }
        return;
    }

    for (int index = 0; index < arraySize; ++index) {
        std::cout << sortedWordsArray[index].word << ": " << sortedWordsArray[index].count << std::endl;
        reportFile << sortedWordsArray[index].word << ": " << sortedWordsArray[index].count << "\n";
    }

    reportFile.close();
    delete[] sortedWordsArray;
}
