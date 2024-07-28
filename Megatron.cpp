#include "Megatron.h"

Megatron::Megatron(): buffManager(REPLACER_TYPE){//2: clockreplacer
    buffManager.setDiskManRef(&diskMan);
    excEngine.setBuffManRef(&buffManager);
}

void Megatron::setDisk(int* measures) {
    diskMan.setDisk(measures);
}

void Megatron::loadfromDisk() {
    diskMan.loadfromDisk();
    excEngine.readSchemasFromFile();
}

void Megatron::printInfo() {
    diskMan.printInfo();
}

void Megatron::createRelation(vector<string> &relation) {
    //int blockId = diskMan.allocRandomBlock();
    excEngine.createRelation(relation);
}

void Megatron::insertRecord(vector<string> &record) {
    excEngine.insertRecord(record);
}

void Megatron::readFile() {
    string filename, recordType;
    cout << "nombre del archivo:" << endl;
    cin >> filename;
    ifstream file("../Data/" + filename + ".csv");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename + ".csv" << endl;
    }
    //definir tipo de registro: longitud fija o variable
    cin >> recordType;
    string line, word;
    vector<string> relation = {filename, recordType};
    vector<int> maxColumnSizes;
    //calcula el tamaño maximo de cada columna
    while (getline(file, line)) {
        istringstream iss(line);
        int column = 0;
        while (getline(iss, word, ';')) {
            if (column >= maxColumnSizes.size()) {
                maxColumnSizes.push_back(word.size());
            } else {
                maxColumnSizes[column] = max(maxColumnSizes[column], static_cast<int>(word.size()));
            }
            ++column;
        }
    }

    file.clear();
    file.seekg(0, ios::beg);

    //crear tabla
    getline(file, line);
    istringstream iss(line);
    int column = 0;
    while (getline(iss, word, ';')) {
        relation.push_back(word);
        cout << "Ingrese el tipo de dato para " << word << ":" << endl;
        cin >> word;
        relation.push_back(word);
        relation.push_back(to_string(maxColumnSizes[column]));
        ++column;
    }
    createRelation(relation);
    // Insertar registros
    while (getline(file, line)) {
        iss.clear();
        iss.str(line);
        vector<string> record = {filename}; // Agregar el nombre del archivo al principio del registro
        while (getline(iss, word, ';')) {
            record.push_back(word);
        }
        cout << endl;
        insertRecord(record);
    }

    file.close();
}

string Megatron::selectPost(int postId) {
    string record = excEngine.selectPost(postId);
    return record;
}
