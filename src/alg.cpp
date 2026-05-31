#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  int ch;

  while ((ch = file.get()) != EOF) {
    if ((ch >= 'A' && ch <= 'Z') ||
        (ch >= 'a' && ch <= 'z')) {
      word += (char)std::tolower(ch);
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty())
    tree.insert(word);

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.getAllWords();

  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });

  std::ofstream out("../result/freq.txt");

  for (const auto& item : words) {
    std::cout << item.first << " : " << item.second << std::endl;

    if (out)
      out << item.first << " : " << item.second << std::endl;
  }

  out.close();
}
