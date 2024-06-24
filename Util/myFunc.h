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

#define PAGE_SIZE 512
#define SECTOR_X_BLOCK 1

#define NUM_FRAMES 5
#define REPLACER_TYPE 2 //2: clockreplacer, 1: lru

#define SCHEMA_PATH "../Disk/schemas.txt"

extern size_t intSize;

namespace myFunc {
  //strings
  void trim(string &str);
  std::string padString(const std::string& input, size_t size);
  string getSubstringBeforeFirst(const std::string& input, char delimiter);
  bool startsWith(const std::string& str, const std::string& prefix);
  //files
  void createDirectory(const std::string& directoryPath);
  bool doesFolderExist(const std::string& folderPath);
  //Random number
  int generateRandomNumber(int lower, int upper);
}

#endif //MYFUNC_H
