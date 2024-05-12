//
// Created by sumire on 5/10/24.
//

#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <iostream>
#include "../Util/myFunc.h"
using namespace std;

#define LL static_cast<long long>

class DiskManager {
private:
    int plattes;
    int surfacesXplat;
    int tracksXsurf;
    int blocksXtrack;
    int bytesXblock;
    int bytesXsector;
    long long int freeSpace;
    map<int, string>blockMaps;
public:
    void loadfromDisk();
    void savetoDisk();
    void saveBlockMap(const int& track);
    void createBlockMap(const int& track);
    void setDisk(int* measures);
    void formatDisk();
};



#endif //DISKMANAGER_H
