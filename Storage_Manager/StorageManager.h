//
// Created by msumi on 11/05/2024.
//

#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include "DiskManager.h"
#include "FileManager.h"

class StorageManager {
private:
  DiskManager diskMan;
  FileManager fileMan;
public:
  void setDisk(int* measures);
  void load();
};



#endif //STORAGEMANAGER_H
