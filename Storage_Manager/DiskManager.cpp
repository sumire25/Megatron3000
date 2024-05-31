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

void DiskManager::loadBlockMap(const int &track) {
    ifstream diskMetadata("../Disk/"+to_string(track)+"/0_0_0.txt");
    if (!diskMetadata.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+to_string(track)+"/0_0_0.txt"<< endl;
    }
    string blockMap;
    diskMetadata >> blockMap;
    blockMaps[track] = blockMap;
    diskMetadata.close();
}

void DiskManager::createBlockMap(const int &track) {
    int blocksXcillinder = plattes*surfacesXplat*blocksXtrack - 1;
    myFunc::createDirectory("../Disk/"+to_string(track));
    ofstream diskMetadata("../Disk/"+to_string(track)+"/0_0_0.txt");
    if (!diskMetadata.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+to_string(track)+"/0_0_0.txt"<< endl;
    }
    blockMaps[track] = "1" + string(blocksXcillinder, '0');
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
    ofstream diskConfig("../Disk/config.txt");
    if (!diskConfig.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/config.txt"<< endl;
    }
    diskConfig << plattes << endl;
    diskConfig << surfacesXplat << endl;
    diskConfig << tracksXsurf << endl;
    diskConfig << blocksXtrack << endl;
    diskConfig << bytesXblock << endl;
    diskConfig << bytesXsector << endl;
    diskConfig << freeSpace << endl;
    diskConfig.close();
    printInfo();
}

void DiskManager::printInfo() {
    cout<<"Capacidad del disco: "<<totalSpace<<" B\n";
    cout<<"Capacidad disponible: "<<freeSpace<<" B\n";
    cout<<"Capacidad del bloque: "<<bytesXblock<<" B\n";
    cout<<"Numero de bloques: "<<totalSpace/LL(bytesXblock)<<"\n";
    cout<<"Capacidad del sector: "<<bytesXsector<<" B\n";
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

int DiskManager::allocNextBlock(const int &blockHeader) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = (blockHeader+1) / blocksPerCylinder;
    int blockCylinder = blockHeader % blocksPerCylinder;

    for(; track<tracksXsurf*surfacesXplat*plattes; track++) {
        if(blockMaps.find(track) == blockMaps.end()) {
            createBlockMap(track);
            setBlockUsed(track, track*blocksPerCylinder + 1);
            return track*blocksPerCylinder + 1;
        }
        for(; blockCylinder<blocksPerCylinder; blockCylinder++) {
            if(isBlockFree(track, blockCylinder)) {
                setBlockUsed(track, blockCylinder);
                return track*blocksPerCylinder + blockCylinder;
            }
        }
        blockCylinder = 0;
    }
    return -1;//no hay bloques libres
}

string DiskManager::readBlock(const int &blockId) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = (blockId+1) / blocksPerCylinder;
    if(blockMaps.find(track) == blockMaps.end()) {
        loadBlockMap(track);
    }
    //
    ifstream blockFile("../Disk/"+blockfileFromId(blockId)+".txt");
    if (!blockFile.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+blockfileFromId(blockId)+".txt"<< endl;
    }
    string content;
    blockFile >> content;
    blockFile.close();
    return content;
}

bool DiskManager::isBlockFree(const int &track, const int &blockId) {
    return blockMaps[track][blockId] == '0';
}

void DiskManager::setBlockUsed(const int &track, const int &blockId) {
    blockMaps[track][blockId] = '1';
    saveBlockMap(track);
}

string DiskManager::blockfileFromId(const int &blockId) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = blockId / blocksPerCylinder;
    cerr << "blocksPerCylinder: "<<blocksPerCylinder<<", track: "<<track<<endl;
    int blockInCylinder = blockId % blocksPerCylinder;
    int plate = blockInCylinder / (surfacesXplat * blocksXtrack);
    int blockInPlate = blockInCylinder % (surfacesXplat * blocksXtrack);
    int surface = blockInPlate / blocksXtrack;
    int block = blockInPlate % blocksXtrack;

    string blockFile = to_string(track) + "/" + to_string(plate) + "_" + to_string(surface) + "_" + to_string(block);
    return blockFile;
}

void DiskManager::writeBlock(const int &blockId, const string &content) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = (blockId+1) / blocksPerCylinder;
    if(blockMaps.find(track) == blockMaps.end()) {
        loadBlockMap(track);
    }
    //
    ofstream blockFile("../Disk/"+blockfileFromId(blockId)+".txt");
    if (!blockFile.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+blockfileFromId(blockId)+".txt"<< endl;
    }
    blockFile << content;
    blockFile.close();
}

