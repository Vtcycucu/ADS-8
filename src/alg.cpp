// Copyright 2021 NNTU-CS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error" << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        unsigned char c = static_cast<unsigned char>(ch);

        if (std::isalpha(c)) {
            word += static_cast<char>(std::tolower(c));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.getAllWords();

    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& w : words) {
        std::cout << w.first << " " << w.second << "\n";
        out << w.first << " " << w.second << "\n";
    }
}
