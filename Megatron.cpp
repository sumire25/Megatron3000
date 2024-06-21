//
// Created by sumire on 5/10/24.
//

#include "Megatron.h"

Megatron::Megatron(): buffManager(2){//2: clockreplacer
    buffManager.setDiskManRef(&diskMan);
    excEngine.setBuffManRef(&buffManager);
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
    //excEngine.printSchemas();
}

void Megatron::insertRecord(vector<string> &record) {
    string relName = record[0];
    excEngine.insertRecord(record);
    /*string record_;
    int blockId;
    record_ = excEngine.formatRecord(record);
    blockId = excEngine.getBlock(record[0]);
    diskMan.writeBlock(record_, blockId);*/
}

void Megatron::leerBloque(int numBlock) {
    if(!buffManager.pinPage(numBlock, RequestType::READ)) return;
    Page* bloque = buffManager.getPage(numBlock);
    cout<<*(bloque->data)<<endl;
}

void Megatron::escribirBloque(int numBloque) {
    if(!buffManager.pinPage(numBloque, RequestType::WRITE)) return;
    Page* bloque = buffManager.getPage(numBloque);
    cout<<*(bloque->data)<<endl;
}

void Megatron::liberarBloque(int numBloque) {
    buffManager.unpinPage(numBloque);
}

void Megatron::mostrarContadores() {
    cout << "Total Misscount: " << buffManager.getMissCount();
    cout << ", Total Hitcount: " << buffManager.getHitcount() << endl;
}

void Megatron::pinPage(int numBloque) {
    buffManager.pinningPage(numBloque);
}

void Megatron::unpinPage(int numBloque) {
    buffManager.unpinningPage(numBloque);
}

void Megatron::print() {
    buffManager.printRequestQueue();
    buffManager.printPageTable();
    buffManager.printReplacer();
}
