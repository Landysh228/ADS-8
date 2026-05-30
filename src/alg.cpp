#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <cctype>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filenick) {
    std::ifstream srcFile(filenick);

    if (!srcFile.is_open()) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string crrntWord = "";
    int crretChar = srcFile.get();

    while (crrntChar != EOF) {
        if (std::isalpha(crrntChar)) {
            crrntWord += static_cast<char>(std::tolower(crrntChar));
        } else {
            if (!crrntWord.empty()) {
                tree.insert(crrntWord);
                crrntWord.clear();
            }
        }
        crrntChar = srcFile.get();
    }

    if (!crrntWord.empty()) {
        tree.insert(crrntWord);
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
