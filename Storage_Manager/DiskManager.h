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
    unordered_map<int, string> blockMaps;//no se hacen muchas reservas de bloques nuevos(podria eliminarse)
public:
    void loadfromDisk();//cargar metadata del disco y sgdb
    void setDisk(int* measures);

    //Guarda el bitmap de los bloques de un track
    void saveBlockMap(const int& track);
    void loadBlockMap(const int& track);
    void createBlockMap(const int& track);
    bool isBlockFree(const int& track, const int& blockId);
    void setBlockUsed(const int& track, const int& blockId);
    string blockfileFromId(const int &blockId);

    int allocRandomBlock();
    int allocNextBlock(const int & blockHeader);
    string readBlock(const int& blockId);
    void writeBlock(const int &blockId, const string &content);
    void printInfo();
};



#endif //DISKMANAGER_H
