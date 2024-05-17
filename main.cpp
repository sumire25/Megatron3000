#include <fstream>



#include "Megatron.h"

void displayMenu();
void handleChoice(int choice);
void readFile();
void configDisco();
std::vector<std::string> getStringsFromCin();

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
    cout << "8. Crear tabla "<<endl;
    cout << "9. Crear disco por defecto "<<endl;
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
        case 3:{
            vector<string> relation = {"Student","15","miki"};
            megatron.insertRecord(relation);
        }
            break;
        case 4:
            cout << "Consulta: "<<endl;
            break;
        case 5:
            cout << "format" << endl;
            break;
        case 6:
            megatron.printInfo();
            break;
        case 7:
        	configDisco();
            break;
        case 8: {
            vector<string> relation = {"Student","age", "int", "8", "name", "char", "10"};
            megatron.createRelation(relation);
            }
            break;
        case 9: {
            int measures[6] = {8, 2, 16384, 128, 4096, 1};
            megatron.setDisk(measures);
        }
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
    string filename;
    cout << "nombre del archivo: ";
    cin >> filename;
    ifstream file("../Data/" + filename + ".csv");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename + ".csv" << endl;
    }

    string line, word;
    vector<string> relation = {filename};
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
        cout << "Ingrese el tipo de dato para " << word << ": ";
        cin >> word;
        relation.push_back(word);
        relation.push_back(to_string(maxColumnSizes[column]));
        ++column;
    }

    // Escribir en disco
    megatron.createRelation(relation);

    // Leer cada línea del archivo a partir de la segunda línea
    getline(file, line);  // Descartar la primera línea
    while (getline(file, line)) {
        iss.clear();
        iss.str(line);
        vector<string> record = {filename};  // Agregar el nombre del archivo al principio del registro
        while (getline(iss, word, ';')) {
            record.push_back(word);
        }
        megatron.insertRecord(record);
    }

    file.close();
}