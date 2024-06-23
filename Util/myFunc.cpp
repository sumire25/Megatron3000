//
// Created by sumire on 5/10/24.
//

#include "myFunc.h"

size_t intSize = 8;

namespace myFunc {
    void trim(string &str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');

        str.erase(0,first);
        str.erase(last+1, str.length());
    }
    //
    std::string padString(const std::string& input, size_t size) {
        if (input.size() >= size) {
            return input;
        } else {
            return input + std::string(size - input.size(), ' ');
        }
    }

    string getSubstringBeforeFirst(const std::string &input, char delimiter) {
        size_t pos = input.find(delimiter);
        if (pos != std::string::npos) {
            return input.substr(0, pos);
        } else {
            return input; // If delimiter not found, return the entire string
        }
    }

    bool startsWith(const std::string &str, const std::string &prefix) {
        return str.compare(0, prefix.size(), prefix) == 0;
    }

    void createDirectory(const std::string& directoryPath) {
        std::filesystem::path pathToCreate = directoryPath;
        if (!std::filesystem::exists(pathToCreate)) {
            if (std::filesystem::create_directory(pathToCreate)) {
                std::cout << "Directory created successfully." << std::endl;
            } else {
                std::cerr << "Error creating directory." << std::endl;
            }
        } else {
            std::cerr << "Directory already exists: "<< directoryPath << std::endl;
        }
    }

    bool doesFolderExist(const std::string& folderPath) {
        return std::filesystem::exists(folderPath);
    }

    int generateRandomNumber(int lower, int upper) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(lower, upper);
        return dis(gen);
    }
}
