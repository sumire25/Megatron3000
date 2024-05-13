//
// Created by sumire on 5/10/24.
//

#ifndef MYFUNC_H
#define MYFUNC_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>
#include <filesystem>
#include <random>
using namespace std;

extern size_t intSize;

namespace myFunc {
  //strings
  void trim(string &str);
  std::string padString(const std::string& input, size_t size);
  string getSubstringBeforeFirst(const std::string& input, char delimiter);
  bool startsWith(const std::string& str, const std::string& prefix);
  //files
  void createDirectory(const std::string& directoryPath);
  //Random number
  int generateRandomNumber(int lower, int upper);
}

#endif //MYFUNC_H
