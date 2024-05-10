//
// Created by sumire on 5/10/24.
//

#ifndef MEGATRON_H
#define MEGATRON_H

#include "Storage_Manager/DiskManager.h"
#include "Query_Processor/Parser.h"

class Megatron {
private:
    DiskManager diskMan;
    Parser myParser;
public:
    void load();
    void createDisk(int* measures);
};



#endif //MEGATRON_H
