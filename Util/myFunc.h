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
using namespace std;

extern size_t intSize;

namespace myFunc {
  void greet();
  int add(int a, int b);
  void trim(string &str);
  std::string padString(const std::string& input, size_t size);
  string getSubstringBeforeFirst(const std::string& input, char delimiter);
  bool startsWith(const std::string& str, const std::string& prefix);
  void createDirectory(const std::string& directoryPath);
}

#endif //MYFUNC_H
