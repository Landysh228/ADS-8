#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  <cctype>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream srcFile(filename);

    if (!srcFile.is_open()) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string token = "";
    int symbol = srcFile.get();

    while (symbol != EOF) {
        if (std::isalpha(symbol)) {
            token += static_cast<char>(std::tolower(symbol));
        } else {
            if (!token.empty()) {
                tree.insert(token);
                token.clear();
            }
        }
        symbol = srcFile.get();
    }

    if (!token.empty()) {
        tree.insert(token);
    }

    srcFile.close();
}

void printFreq(BST<std::string>& tree) {
    BST<std::string>::Pair* sortedData = nullptr;
    int dataSize = tree.getSortedArray(sortedData);

    std::ofstream reportFile("result/freq.txt");
    if (!reportFile.is_open()) {
        std::cout << "Error creating result file!" << std::endl;
        if (sortedData != nullptr) {
            delete[] sortedData;
        }
        return;
    }

    for (int idx = 0; idx < dataSize; ++idx) {
        std::cout << sortedData[idx].word << ": " << sortedData[idx].count << std::endl;
        reportFile << sortedData[idx].word << ": " << sortedData[idx].count << "\n";
    }

    reportFile.close();
    delete[] sortedData;
}
