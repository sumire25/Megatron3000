//
// Created by sumire on 5/10/24.
//

#include "DiskManager.h"

#include <fstream>

void DiskManager::loadfromDisk() {
    cout<<"manager\n";
}

void DiskManager::saveFreeBlockMap(const int &track) {
    ofstream diskMetadata("../Disk/"+to_string(track)+"/0_0_0.txt");
    if (!diskMetadata.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+to_string(track)+"/0_0_0.txt"<< endl;
    }
    diskMetadata << FreeblockMaps[track];
    diskMetadata.close();
}

void DiskManager::loadFreeBlockMap(const int &track) {
    ifstream diskMetadata("../Disk/"+to_string(track)+"/0_0_0.txt");
    if (!diskMetadata.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+to_string(track)+"/0_0_0.txt"<< endl;
    }
    string FreeblockMap;
    diskMetadata >> FreeblockMap;
    FreeblockMaps[track] = FreeblockMap;
    diskMetadata.close();
}

void DiskManager::createFreeBlockMap(const int &track) {
    int blocksXcillinder = plattes*surfacesXplat*blocksXtrack;
    string freeblockMap = "1" + string(blocksXcillinder-1, '0');
    //crear archivo de bitmap
    myFunc::createDirectory("../Disk/"+to_string(track));
    ofstream diskMetadata("../Disk/"+to_string(track)+"/0_0_0.txt");
    if (!diskMetadata.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/"+to_string(track)+"/0_0_0.txt"<< endl;
    }
    diskMetadata << freeblockMap;
    diskMetadata.close();
    freeSpace -= bytesXblock;
}

bool DiskManager::existFreeBlockMap(const int &track) {
    return myFunc::doesFolderExist("../Disk/"+to_string(track));
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
    createFreeBlockMap(0);
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
        if(FreeblockMaps.find(track) == FreeblockMaps.end()) {
            //REFACTOR
            createFreeBlockMap(track);
            setBlockUsed(track, blockId % blocksPerCylinder);
            done = true;
        } else {
            if(isBlockFree(track, blockId % blocksPerCylinder)) {
                setBlockUsed(track, blockId % blocksPerCylinder);
                done = true;
            }
        }
    }while (!done);
    createBlockFile(blockId);
    return blockId;
}

int DiskManager::allocNextBlock(const int &blockHeader) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = (blockHeader+1) / blocksPerCylinder;
    int blockCylinder = blockHeader % blocksPerCylinder;
    int blockId;

    for(; track<tracksXsurf; track++) {
        if(FreeblockMaps.find(track) == FreeblockMaps.end()) {
            createFreeBlockMap(track);
            blockId = track*blocksPerCylinder + 1;
            setBlockUsed(track, 1);
            createBlockFile(blockId);
            return blockId;
        }
        for(; blockCylinder<blocksPerCylinder; blockCylinder++) {
            if(isBlockFree(track, blockCylinder)) {
                setBlockUsed(track, blockCylinder);
                blockId = track*blocksPerCylinder + blockCylinder;
                createBlockFile(blockId);
                return blockId;
            }
        }
        blockCylinder = 0;
    }
    cerr<<"allocNextBlock: No hay bloques libres"<<endl;
    return -1;
}

string DiskManager::readBlock(const int &blockId) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = (blockId+1) / blocksPerCylinder;
    if(FreeblockMaps.find(track) == FreeblockMaps.end()) {
        loadFreeBlockMap(track);
    }

    int sectorXblock = bytesXblock/bytesXsector;
    ifstream file;
    string content, line;
    string sectorFile = firstSectorFileFromId(blockId);
    for(int i=0; i<sectorXblock; i++) {
        file.open("../Disk/"+sectorFile+".txt");
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo(read): "<<"../Disk/"+sectorFile+".txt"<< endl;
        }
        else {
            file >> line;
            content += line;
            file.close();
        }
        incrementSectorPath(sectorFile);
    }
    sectorFile = firstSectorFileFromId(blockId);
    ofstream blockFile("../Disk/"+sectorFile+"_b"+to_string(blockId)+".txt");
    if (!blockFile.is_open()) {
        cerr << "Error al abrir el archivo(read): "<<"../Disk/"+sectorFile+"_b"+to_string(blockId)+".txt"<< endl;
    }
    blockFile << content;
    blockFile.close();
    return content;
}

bool DiskManager::isBlockFree(const int &track, const int &blockId) {
    return FreeblockMaps[track][blockId] == '0';
}

void DiskManager::setBlockUsed(const int &track, const int &blockId) {
    FreeblockMaps[track][blockId] = '1';
    saveFreeBlockMap(track);
}

string DiskManager::firstSectorFileFromId(const int &blockId) {
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = blockId / blocksPerCylinder;
    //cerr << "blocksPerCylinder: "<<blocksPerCylinder<<", track: "<<track<<endl;
    int blockInCylinder = blockId % blocksPerCylinder;
    int plate = blockInCylinder / (surfacesXplat * blocksXtrack);
    int blockInPlate = blockInCylinder % (surfacesXplat * blocksXtrack);
    int surface = blockInPlate / blocksXtrack;
    int block = blockInPlate % blocksXtrack;
    int sector = block * (bytesXblock/bytesXsector);
    string blockFile = to_string(track) + "/" + to_string(plate) + "_" + to_string(surface) + "_" + to_string(sector);
    return blockFile;
}

void DiskManager::createBlockFile(const int &blockId) {
    std::ofstream createFile;
    string sectorFile = firstSectorFileFromId(blockId);
    createFile.open("../Disk/"+sectorFile+"_b"+to_string(blockId)+".txt");
    createFile << string(bytesXblock, ' ');
    createFile.close();
    int sectorXblock = bytesXblock/bytesXsector;
    for(int i=0; i<sectorXblock; i++) {
        createFile.open("../Disk/"+sectorFile+".txt");
        createFile << string(bytesXsector, ' ');
        createFile.close();
        incrementSectorPath(sectorFile);
    }
}

void DiskManager::incrementSectorPath(string& sectorPath) {
    size_t lastUnderscore = sectorPath.find_last_of('_');
    int lastNumber = std::stoi(sectorPath.substr(lastUnderscore + 1));
    sectorPath.replace(lastUnderscore + 1, std::string::npos, std::to_string(++lastNumber));
}

void DiskManager::writeBlock(const int &blockId, const string &content) {
    //To load FreeblockMap of the next cilynder wich could have pages from the same file
    int blocksPerCylinder = plattes * surfacesXplat * blocksXtrack;
    int track = (blockId+1) / blocksPerCylinder;
    if(FreeblockMaps.find(track) == FreeblockMaps.end()) {
        loadFreeBlockMap(track);
    }

    int sectorXblock = bytesXblock/bytesXsector;
    string sectorFile = firstSectorFileFromId(blockId);
    ofstream file;
    file.open("../Disk/"+sectorFile+"_b"+to_string(blockId)+".txt");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo(write): "<<"../Disk/"+sectorFile+"_b"+to_string(blockId)+".txt"<< endl;
    }
    file << content;
    file.close();
    for(int i=0; i<sectorXblock; i++) {
        file.open("../Disk/"+sectorFile+".txt");
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo(write): "<<"../Disk/"+sectorFile+".txt"<< endl;
        }
        else {
            string sub = content.substr(i*bytesXsector, bytesXsector);
            cerr << "Write: '"<<sub<<"'"<<endl;
            file << sub;
            file.close();
        }
        incrementSectorPath(sectorFile);
    }
}

