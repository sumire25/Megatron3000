//
// Created by sumire on 5/10/24.
//

#include "DiskManager.h"

#include <fstream>

void DiskManager::loadfromDisk() {
    cout<<"manager\n";
}

void DiskManager::savetoDisk() {
    //iterar el blockMaps y guardar en sus archivos
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
    totalSpace = freeSpace;
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
    printInfo();
}

void DiskManager::printInfo() {
    cout<<"Capacidad del disco: "<<totalSpace<<"B\n";
    cout<<"Capacidad disponible: "<<freeSpace<<"B\n";
    cout<<"Capacidad del bloque: "<<bytesXblock<<"B\n";
    cout<<"Numero de bloques: "<<totalSpace/LL(bytesXblock)<<"\n";
    cout<<"Capacidad del sector: "<<bytesXsector<<"B\n";
    cout<<"Numero de sctores: "<<totalSpace/LL(bytesXsector)<<"\n";
}

int DiskManager::allocRandomBlock() {
    bool done = false;
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track, blockId;
    do {
        blockId = myFunc::generateRandomNumber(0, plattes*surfacesXplat*tracksXsurf*blocksXtrack - 1);
        track = blockId / blocksPerCylinder;
        if(blockMaps.find(track) == blockMaps.end()) {
            createBlockMap(track);
            setBlockUsed(track, blockId % blocksPerCylinder);
            done = true;
        } else {
            if(isBlockFree(track, blockId % blocksPerCylinder)) {
                setBlockUsed(track, blockId % blocksPerCylinder);
                done = true;
            }
        }
    }while (!done);
    return blockId;
}

bool DiskManager::isBlockFree(const int &track, const int &blockId) {
    return blockMaps[track][blockId + intSize] == '0';
}

void DiskManager::setBlockUsed(const int &track, const int &blockId) {
    blockMaps[track][blockId + intSize] = '1';
}

string DiskManager::blockfileFromId(int &blockId) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = blockId / blocksPerCylinder;
    int blockInCylinder = blockId % blocksPerCylinder;
    int plate = blockInCylinder / (surfacesXplat * blocksXtrack);
    int blockInPlate = blockInCylinder % (surfacesXplat * blocksXtrack);
    int surface = blockInPlate / blocksXtrack;
    int block = blockInPlate % blocksXtrack;

    string blockFile = to_string(track) + "/" + to_string(plate) + "_" + to_string(surface) + "_" + to_string(block);
    return blockFile;
}

void DiskManager::writeBlock(string &content, int blockId) {
    ofstream blockFile("../Disk/"+blockfileFromId(blockId)+".txt", ios::app);
    if (!blockFile.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+blockfileFromId(blockId)+".txt"<< endl;
    }
    blockFile << content;
    blockFile.close();
}

