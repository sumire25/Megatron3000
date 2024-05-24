//
// Created by sumire on 5/10/24.
//

#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <iostream>
#include <unordered_map>

#include "../Util/myFunc.h"
using namespace std;

#define LL static_cast<long long>

class DiskManager {
private:
    string diskConfig;
    int plattes;
    int surfacesXplat;
    int tracksXsurf;
    int blocksXtrack;
    int bytesXblock;
    int bytesXsector;
    long long int totalSpace;
    long long int freeSpace;
    unordered_map<int, string> blockMaps;
public:
    void loadfromDisk();
    void savetoDisk();
    void saveBlockMap(const int& track);
    void createBlockMap(const int& track);
    void setDisk(int* measures);
    void printInfo();

    int allocRandomBlock();
    bool isBlockFree(const int& track, const int& blockId);
    void setBlockUsed(const int& track, const int& blockId);
    string blockfileFromId(int& blockId);
    void writeBlock(string& content, int blockId);
};



#endif //DISKMANAGER_H
