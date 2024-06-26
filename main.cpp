#include <fstream>
#include "Megatron.h"

void displayMenu();

void handleChoice(int choice);

void readFile();

void resetMegatron();

Megatron megatron;

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        handleChoice(choice);
    } while (choice != 0 && choice != 9);

    return 0;
}

void displayMenu() {
    cout << "1. Crear disco por defecto" << endl;
    cout << "2. Cargar Megatron" << endl;
    cout << "3. Crear tabla" << endl;
    cout << "4. Añadir nuevo registro" << endl;
    cout << "5. Leer archivo" << endl;
    cout << "6. Leer Pagina" << endl;
    cout << "7. Escribir Pagina" << endl;
    cout << "8. Liberar Pagina" << endl;
    cout << "9. Reset Megatron and quit" << endl;
    cout << "0. Cerrar" << endl;
    cout << "Seleccione una opcion:" << endl;
}

void handleChoice(int choice) {
    switch (choice) {
        case 0:
            cout << "Cerrando Megatron3000." << endl;
            break;
        case 1: {
            int measures[6] = {2, 2, 256, 128, PAGE_SIZE / SECTOR_X_BLOCK, SECTOR_X_BLOCK};
            megatron.setDisk(measures);
        }
        break;
        case 2: {
            cout << "Cargando Megatron..." << endl;
            megatron.loadfromDisk();
        }
        break;
        case 3: {
            vector<string> relation = {"Student", "Fixed", "age", "int", "8", "name", "char", "10"};
            megatron.createRelation(relation);
        }
        break;
        case 4: {
            vector<string> relation = {"Student", "15", "miki"};
            megatron.insertRecord(relation);
        }
        break;
        case 5:
            readFile();
            break;
        case 6: {
            int pageId;
            cin >> pageId;
            megatron.leerBloque(pageId);
        }
        break;
        case 7: {
            int pageId;
            cin >> pageId;
            megatron.escribirBloque(pageId);
        }
        break;
        case 8: {
            int pageId;
            cin >> pageId;
            megatron.liberarBloque(pageId);
        }
        case 9: {
            resetMegatron();
            cout << "Megatron reseteado." << endl;
            break;
        }
        break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

void readFile() {
    string filename, recordType;
    cout << "nombre del archivo:" << endl;
    cin >> filename;
    ifstream file("../Data/" + filename + ".csv");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename + ".csv" << endl;
    }
    cin >> recordType;

    string line, word;
    vector<string> relation = {filename, recordType};
    vector<int> maxColumnSizes;

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

    // Escribir en disco
    megatron.createRelation(relation);

    // Leer cada línea del archivo a partir de la segunda línea
    getline(file, line); // Descartar la primera línea
    while (getline(file, line)) {
        iss.clear();
        iss.str(line);
        vector<string> record = {filename}; // Agregar el nombre del archivo al principio del registro
        while (getline(iss, word, ';')) {
            record.push_back(word);
        }
        megatron.insertRecord(record);
    }

    file.close();
}

void resetMegatron() {

    std::string path = "../Disk/*";
    std::string command = "rm -rf " + path;
    system(command.c_str());
    // crea un nuevo file schemas.txt
    ofstream file("../Disk/schemas.txt");
    file.close();
}
