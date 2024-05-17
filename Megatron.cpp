//
// Created by sumire on 5/10/24.
//

#include "Megatron.h"

void Megatron::setDisk(int* measures) {
    diskMan.setDisk(measures);
    fileMan.setDataDictionary();
}

void Megatron::loadfromDisk() {
    diskMan.loadfromDisk();
}

void Megatron::printInfo() {
    diskMan.printInfo();
}

void Megatron::createRelation(vector<string> &relation) {
    if(!fileMan.hasRelation(relation[0])) {
        fileMan.addSchema(relation, diskMan.allocRandomBlock());
    }
    else
        cerr<<"Relacion ya existente"<<endl;
}

void Megatron::insertRecord(vector<string> &record) {
    string record_ = fileMan.formatRecord(record);
    int blockId = fileMan.getBlock(record[0]);
    diskMan.writeBlock(record_, blockId);
}
