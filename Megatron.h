//
// Created by sumire on 5/10/24.
//

#ifndef MEGATRON_H
#define MEGATRON_H

#include "Storage_Manager/StorageManager.h"
#include "Query_Processor/Parser.h"

class Megatron {
private:
    StorageManager storageMan;
    Parser myParser;
public:
    void load();
    void setDisk(int* measures);
};



#endif //MEGATRON_H
