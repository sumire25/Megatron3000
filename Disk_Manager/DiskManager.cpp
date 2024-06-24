//
// Created by sumire on 5/10/24.
//

#include "DiskManager.h"

#include <fstream>

void DiskManager::loadfromDisk() {
    ifstream diskConfig("../Disk/config.txt");
    if (!diskConfig.is_open()) {
        cerr << "Error al abrir el archivo: "<<"../Disk/config.txt"<< endl;
    }
    diskConfig >> plattes;
    diskConfig >> surfacesXplat;
    diskConfig >> tracksXsurf;
    diskConfig >> blocksXtrack;
    diskConfig >> bytesXblock;
    diskConfig >> bytesXsector;
    diskConfig >> freeSpace;
    diskConfig.close();
    totalSpace = LL(plattes)*LL(surfacesXplat)*LL(tracksXsurf)*LL(blocksXtrack)*LL(bytesXblock);
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
    string freeBlockMap;
    do {
        blockId = myFunc::generateRandomNumber(0, plattes*surfacesXplat*tracksXsurf*blocksXtrack - 1);
        track = blockId / blocksPerCylinder;
        if(!existFreeBlockMap(track)) {
            //REFACTOR
            createFreeBlockMap(track);
            setBlockUsed(track, blockId % blocksPerCylinder);
            done = true;
        } else {
            freeBlockMap = getFreeBlockMap(track);
            if(freeBlockMap[blockId % blocksPerCylinder] == '0') {
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
    int blockCylinder = blockHeader + 1;
    int track = blockCylinder / blocksPerCylinder;
    blockCylinder = blockCylinder % blocksPerCylinder;
    int blockId;
    string freeBlockMap;

    for(; track<tracksXsurf; track++) {
        if(!existFreeBlockMap(track)) {
            createFreeBlockMap(track);
            blockId = track*blocksPerCylinder + 1;
            setBlockUsed(track, 1);
            createBlockFile(blockId);
            return blockId;
        }
        freeBlockMap = getFreeBlockMap(track);
        for(; blockCylinder<blocksPerCylinder; blockCylinder++) {
            if(freeBlockMap[blockCylinder] == '0') {
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
            std::getline(file, line);
            content += line;
            //cerr<<"line: '"<<line<<"'"<<endl;
            //cerr<<"content: '"<<content<<"'"<<endl;
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

void DiskManager::setBlockUsed(const int &track, const int &blockId) {
    string filePath = "../Disk/"+to_string(track)+"/0_0_0.txt";
    std::fstream freeBlockMapFile;
    std::string content;
    // Step 1: Open the file in read mode
    freeBlockMapFile.open(filePath, std::ios::in);
    if (!freeBlockMapFile) {
        cerr << "Error al abrir el archivo: "<<filePath<< endl;
        return;
    }
    getline(freeBlockMapFile, content);
    freeBlockMapFile.close();
    // Step 2: Modify the string
    content[blockId] = '1';
    // Step 3: Open the file in write mode and write the modified string back to the file
    freeBlockMapFile.open(filePath, std::ios::out | std::ios::trunc);
    if (!freeBlockMapFile) {
        cerr << "Error al abrir el archivo: "<<filePath<< endl;
        return;
    }
    freeBlockMapFile << content;
    freeBlockMapFile.close();
}

string DiskManager::getFreeBlockMap(const int &track) {
    string filePath = "../Disk/"+to_string(track)+"/0_0_0.txt";
    std::fstream freeBlockMapFile;
    std::string content;
    // Step 1: Open the file in read mode
    freeBlockMapFile.open(filePath, std::ios::in);
    if (!freeBlockMapFile) {
        cerr << "Error al abrir el archivo: "<<filePath<< endl;
    }
    getline(freeBlockMapFile, content);
    return content;
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
            //cerr << "Write: '"<<sub<<"'"<<endl;
            file << sub;
            file.close();
        }
        incrementSectorPath(sectorFile);
    }
}

