#include "Megatron.h"

Megatron::Megatron(): buffManager(REPLACER_TYPE){//2: clockreplacer
    buffManager.setDiskManRef(&diskMan);
    excEngine.setBuffManRef(&buffManager);
    excEngine.setDiskManRef(&diskMan);
}

void Megatron::setDisk(int* measures) {
    diskMan.setDisk(measures);
    //excEngine.setDataDictionary();
}

void Megatron::loadfromDisk() {
    diskMan.loadfromDisk();
    excEngine.readSchemasFromFile();
}

void Megatron::printInfo() {
    diskMan.printInfo();
}

void Megatron::createRelation(vector<string> &relation) {
    int blockId = diskMan.allocRandomBlock();
    excEngine.createRelation(relation, blockId);
  // if (!hasRelation(relation[0])) {
  //   addSchema(relation, blockId);
  // } else {
  //   cerr << "Relacion ya existente" << endl;
  // }
  // printSchemas();
}

void Megatron::insertRecord(vector<string> &record) {
    excEngine.insertRecord(record);
}


void Megatron::leerBloque(int numBlock) {
    if(!buffManager.pinPage(numBlock, RequestType::READ)) return;
    Page* bloque = buffManager.getPage(numBlock);
    cout<<*(bloque->data)<<endl;
    buffManager.printRequestQueue();
    buffManager.printPageTable();
    buffManager.printReplacer();
}

void Megatron::escribirBloque(int numBloque) {
    if(!buffManager.pinPage(numBloque, RequestType::WRITE)) return;
    Page* bloque = buffManager.getPage(numBloque);
    cout<<*(bloque->data)<<endl;
    buffManager.printRequestQueue();
    buffManager.printPageTable();
    buffManager.printReplacer();
}

void Megatron::liberarBloque(int numBloque) {
    buffManager.unpinPage(numBloque);
    buffManager.printRequestQueue();
    buffManager.printPageTable();
    buffManager.printReplacer();
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
