// Copyright 2021 NNTU-CS

#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
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
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words = tree.getData();

    std::sort(words.begin(), words.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& e : words) {
        std::cout << e.first << " " << e.second << std::endl;
        out << e.first << " " << e.second << std::endl;
    }

    out.close();
}
