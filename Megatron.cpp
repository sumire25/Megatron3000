//
// Created by sumire on 5/10/24.
//

#include "Megatron.h"

void Megatron::setDisk(int* measures) {
    diskMan.setDisk(measures);
    excEngine.setDataDictionary();
}

void Megatron::loadfromDisk() {
    diskMan.loadfromDisk();
}

void Megatron::printInfo() {
    diskMan.printInfo();
}

void Megatron::createRelation(vector<string> &relation) {
    if(!excEngine.hasRelation(relation[0])) {
        excEngine.addSchema(relation, diskMan.allocRandomBlock());
    }
    else
        cerr<<"Relacion ya existente"<<endl;
}

void Megatron::insertRecord(vector<string> &record) {
    string relName = record[0];
    record.erase(record.begin());
    excEngine.insertRecord(relName, record);
    /*string record_;
    int blockId;
    record_ = excEngine.formatRecord(record);
    blockId = excEngine.getBlock(record[0]);
    diskMan.writeBlock(record_, blockId);*/
}
