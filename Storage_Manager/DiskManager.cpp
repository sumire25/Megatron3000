//
// Created by sumire on 5/10/24.
//

#include "DiskManager.h"

#include <fstream>

void DiskManager::loadfromDisk() {
    cout<<"manager\n";
}

void DiskManager::saveBlockMap(const int &track) {
    ofstream diskMetadata("../Disk/"+to_string(track)+"/0_0_0.txt");
    if (!diskMetadata.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+to_string(track)+"/0_0_0.txt"<< endl;
    }
    diskMetadata << blockMaps[track];
    diskMetadata.close();
}

void DiskManager::createBlockMap(const int &track) {
    int blocksXcillinder = plattes*surfacesXplat*blocksXtrack - 1;
    myFunc::createDirectory("../Disk/"+to_string(track));
    ofstream diskMetadata("../Disk/"+to_string(track)+"/0_0_0.txt");
    if (!diskMetadata.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+to_string(track)+"/0_0_0.txt"<< endl;
    }
    blockMaps[track] = myFunc::padString(to_string(blocksXcillinder),intSize);
    blockMaps[track] += "1" + string(blocksXcillinder, '0');
    diskMetadata << blockMaps[track];
    diskMetadata.close();
    freeSpace -= bytesXblock;
}

void DiskManager::setDisk(int *measures) {
    plattes = measures[0];
    surfacesXplat = measures[1];
    tracksXsurf = measures[2];
    blocksXtrack = measures[3]/measures[5];
    bytesXblock = measures[4]*measures[5];
    bytesXsector = measures[4];
    freeSpace = LL(plattes)*LL(surfacesXplat)*LL(tracksXsurf)*LL(blocksXtrack)*LL(bytesXblock);
    cerr<<"free: "<<freeSpace<<endl;
    createBlockMap(0);
    //Escribir capacidades del disco
    blockMaps[0] += myFunc::padString(to_string(plattes),intSize);
    blockMaps[0] += myFunc::padString(to_string(surfacesXplat),intSize);
    blockMaps[0] += myFunc::padString(to_string(tracksXsurf),intSize);
    blockMaps[0] += myFunc::padString(to_string(blocksXtrack),intSize);
    blockMaps[0] += myFunc::padString(to_string(bytesXblock),intSize);
    blockMaps[0] += myFunc::padString(to_string(bytesXsector),intSize);
    blockMaps[0] += myFunc::padString(to_string(freeSpace),16);
    saveBlockMap(0);
    cerr<<"free: "<<freeSpace<<endl;
}
