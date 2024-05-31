//
// Created by sumire on 5/10/24.
//

#include "Megatron.h"

Megatron::Megatron() {
    buffManager.setDiskManRef(&diskMan);
}

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
        int blockId = diskMan.allocRandomBlock();
        excEngine.addSchema(relation, blockId);
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

void Megatron::leerBloque(int numBlock) {
    Page* page = buffManager.getPage(numBlock);
    if(page != nullptr) {
        cout<<*(page->data)<<endl;
        buffManager.printPageTable();
        buffManager.printLRUqueue();
    }
}

void Megatron::escribirBloque(int numBloque, string contenido) {
    Page* page = buffManager.getPage(numBloque);
    if(page != nullptr) {
        *(page->data) = std::move(contenido);
        buffManager.setDirtyFlag(numBloque);
        buffManager.printPageTable();
        buffManager.printLRUqueue();
    }
}

void Megatron::liberarBloque(int numBloque) {
    buffManager.unpinPage(numBloque);
    buffManager.printPageTable();
    buffManager.printLRUqueue();
}

void Megatron::mostrarContadores() {
    cout << "Total Misscount: " << buffManager.getMissCount();
    cout << ", Total Hitcount: " << buffManager.getHitcount() << endl;
}
