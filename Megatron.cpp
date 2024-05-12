//
// Created by sumire on 5/10/24.
//

#include "Megatron.h"

void Megatron::load() {
    myParser.load();
    storageMan.load();
    cout << "Loading\n";
}

void Megatron::setDisk(int *measures) {
    storageMan.setDisk(measures);
}
