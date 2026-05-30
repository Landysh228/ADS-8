// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string buf = "";

    while (!file.eof()) {
        int ch = file.get();

        if (ch >= 'A' && ch <= 'Z') {
            buf += static_cast<char>(ch + 32);
        } else if (ch >= 'a' && ch <= 'z') {
            buf += static_cast<char>(ch);
        } else {
            if (!buf.empty()) {
                tree.insert(buf);
                buf = "";
            }
        }
    }

    if (!buf.empty()) {
        tree.insert(buf);
    }

    file.close();
}

bool cmp(std::pair<std::string, int> a,
         std::pair<std::string, int> b) {
    return a.second > b.second;
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> vec;

    tree.getWords(&vec);

    std::sort(vec.begin(), vec.end(), cmp);

    std::ofstream fout("result/freq.txt");

    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i].first
                  << " "
                  << vec[i].second
                  << std::endl;

        fout << vec[i].first
             << " "
             << vec[i].second
             << std::endl;
    }

    fout.close();
}
