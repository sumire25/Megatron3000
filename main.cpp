#include <fstream>
#include <iostream>
#include "Megatron.h"

void displayMenu();
void handleChoice(int choice);
void readFile();
void configDisco();

Megatron megatron;

int main()
{
  cout << "Bienvenido a Megatron3000!" << endl;

  int choice;
  do {
      displayMenu();
      cin >> choice;
      handleChoice(choice);
  } while (choice != 0);

  return 0;
}

void displayMenu() {
    cout << "1. Cargar Megatron" << endl;   // crear archivos y setear data dictionary
    cout << "2. Leer archivo" << endl;  // leer todo o n registros

    // En qué plato, superficie, pista, sector y bloque
    // Al crear relacion definir longitud fija o varaiable
    cout << "3. Añadir nuevo registro" << endl; //
    cout << "4. Hacer una consulta" << endl;    //
        // eliminar registro

    cout << "5. Formatear Disco " << endl;  // Limpiar contenidos de los bloques
    cout << "6. Informacion del Disco " << endl;    // total, libre, ocupada, bloque, sector
    cout << "7. Configurar disco "<<endl;
    cout << "0. Cerrar" << endl;
    cout << "Seleccione una opcion: ";
}

void handleChoice(int choice) {
    switch(choice) {
        case 0:
            cout << "Cerrando Megatron3000." << endl;
            break;
        case 1:
            cout << "Cargando Megatron..." << endl;
            break;
        case 2:
        	readFile();
            break;
        case 3:
            cout << "añadir registro\n";
            break;
        case 4:
            cout << "Consulta: "<<endl;
            break;
        case 5:
            cout << "format" << endl;
            break;
        case 6:
            cout << "info\n";
            break;
        case 7:
        	configDisco();
          break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

void configDisco() {
	int params[6];
	cout << "Ingresar en orden, numero de:\n platos\n superficies por plato\n pistas por superficie\n sectores por pista\n bytes por sector\n sectores por bloque\n";
	for(int i=0; i<6; i++)
		cin >> params[i];
	megatron.setDisk(params);
}

// Adicionar N registros de un *.csv
void readFile() {
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;

    std::ifstream file("../Data/"+filename+".csv");
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    int numRecords;
    std::cout << "Enter the number of records to read: ";
    std::cin >> numRecords;

    std::string line;
    std::getline(file, line); // read the first line to get the column names
    std::istringstream iss(line);
    std::vector<std::string> columnNames;
    std::string word;
    while (std::getline(iss, word, ';')) {
        columnNames.push_back(word);
    }

    std::vector<std::string> columnTypes(columnNames.size());
    std::vector<bool> isVariableLength(columnNames.size());
    for (int i = 0; i < columnNames.size(); ++i) {
        std::cout << "Enter the data type for column " << columnNames[i] << ": ";
        std::cin >> columnTypes[i];
        if (columnTypes[i] == "char") {
            char variableLength;
            std::cout << "Is column " << columnNames[i] << " of variable length? (y/n): ";
            std::cin >> variableLength;
            isVariableLength[i] = (variableLength == 'y');
        }
    }

    std::vector<int> maxLengths(columnNames.size(), 0);
    for (int i = 0; i < numRecords; ++i) {
        if (!std::getline(file, line)) {
            break; // end of file or other error
        }
        iss.clear();
        iss.str(line);
        for (int j = 0; j < columnNames.size(); ++j) {
            if (!std::getline(iss, word, ';')) {
                break; // end of line or other error
            }
            if (!isVariableLength[j]) {
                maxLengths[j] = std::max(maxLengths[j], static_cast<int>(word.size()));
            }
        }
    }

    file.close();

    // print the column names, types, and lengths
    for (int i = 0; i < columnNames.size(); ++i) {
        std::cout << "Column: " << columnNames[i] << ", Type: " << columnTypes[i];
        if (!isVariableLength[i]) {
            std::cout << ", Max Length: " << maxLengths[i];
        }
        std::cout << std::endl;
    }
}