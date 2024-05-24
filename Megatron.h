//
// Created by sumire on 5/10/24.
//

#ifndef MEGATRON_H
#define MEGATRON_H

#include "Storage_Manager/DiskManager.h"
#include "Query_Processor/ExecutionEngine.h"

#include "Query_Processor/Parser.h"

class Megatron {
private:
    DiskManager diskMan;
    ExecutionEngine excEngine;
    Parser myParser;
public:
    void setDisk(int* measures);
    void loadfromDisk();
    void printInfo();
    void createRelation(vector<string>& relation);
    void insertRecord(vector<string>& record);
    void selectRecord(vector<string>& record);
    void deleteRecord(vector<string>& record);
};



#endif //MEGATRON_H
