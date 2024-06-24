#include <fstream>
#include "Megatron.h"

void displayMenu();
void handleChoice(int choice);
void readFile();
void configDisco();
std::vector<std::string> getStringsFromCin();

Megatron megatron;
DiskManager diskMan;

void displayMenu_() {
    cout << "1. Random" << endl;   // crear archivos y setear data dictionary
    cout << "2. Next" << endl;  // leer todo o n registros
    cout << "3. read" << endl; //
    cout << "4. write" << endl;
    cout << "5. Formatear Disco " << endl;  // Limpiar contenidos de los bloques
    cout << "6. Informacion del Disco " << endl;    // total, libre, ocupada, bloque, sector
    cout << "0. Cerrar" << endl;
    cout << "Seleccione una opcion:" << endl;
}

void handleChoice_(int choice) {
    switch(choice) {
        case 0:
            cout << "Cerrando Megatron3000." << endl;
        break;
        case 1: {
            int blockId = diskMan.allocRandomBlock();
            cout<<"\tReservado: "<<blockId<<endl;
        }
        break;
        case 2: {
            int head;
            cin>>head;
            int blockId = diskMan.allocNextBlock(head);
            cout<<"\tReservado: "<<blockId<<endl;
        }
        break;
        case 3:{
            int head;
            cin>>head;
            string content = diskMan.readBlock(head);
            cout<<"'"<<content<<"'"<<endl;
        }
        break;
        case 4:{
            int head;
            cin>>head;
            char c;
            cin >> c;
            string content = string(PAGE_SIZE, c);
            diskMan.writeBlock(head, content);
        }
        break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

int main()
{
    /*int opc = 1;
    int bloque;
    std::string contenido;

    //Interfaz interfaz(5, 10, 3);
    Megatron interfaz;
    int measures[6] = {2, 2, 256, 128, 512, 1};
    interfaz.setDisk(measures);

    do {
        std::cout << "----------- Operaciones -----------" <<std::endl;
        std::cout << "1. Leer bloque " <<std::endl;
        std::cout << "2. Escribir bloque " <<std::endl;
        std::cout << "3. Liberar bloque " <<std::endl;
        std::cin >> opc;
        std::cout << "\n Indique el id del bloque: " <<std::endl;

        switch (opc)
        {
            case 1: {
                std::cin >> bloque;
                interfaz.leerBloque(bloque);
            }
            break;

            case 2:{
                std::cin >> bloque;
                std::cin >> contenido;
                interfaz.escribirBloque(bloque,contenido);
            }
            break;

            case 3:{
                std::cin >> bloque;
                interfaz.liberarBloque(bloque);
            }
            break;

            default:
                break;
        }


    } while (opc);

    interfaz.mostrarContadores();

    return 0; */

    /*int sectorXblock = 2;
    int measures[6] = {2, 2, 256, 128, PAGE_SIZE/sectorXblock, sectorXblock};
    diskMan.setDisk(measures);
  cout << "Bienvenido a Megatron3000!" << endl;
    int choice;
    do {
        displayMenu_();
        cin >> choice;
        handleChoice_(choice);
    } while (choice != 0);*/

    int choice;
  do {
      displayMenu();
      cin >> choice;
      handleChoice(choice);
  } while (choice != 0);

  return 0;
}

void displayMenu() {
    cout << "1. Crear disco por defecto" << endl;
    cout << "2. Cargar Megatron" << endl;
    cout << "3. Crear tabla" << endl;
    cout << "4. Añadir nuevo registro" << endl;
    cout << "5. Leer archivo" << endl;
    cout << "6. Hacer una consulta" << endl;
    cout << "7. Formatear Disco " << endl;
    cout << "8. Informacion del Disco " << endl;
    cout << "9. Configurar disco " << endl;
    cout << "0. Cerrar" << endl;
    cout << "Seleccione una opcion:" << endl;
}

void handleChoice(int choice) {
    switch(choice) {
        case 0:
            cout << "Cerrando Megatron3000." << endl;
        break;
        case 1: {
            int sectorXblock = 1;
            int measures[6] = {2, 2, 256, 128, PAGE_SIZE/sectorXblock, sectorXblock};
            megatron.setDisk(measures);
        }
        break;
        case 2:
            cout << "Cargando Megatron..." << endl;
        break;
        case 3: {
            vector<string> relation = {"Student","Fixed","age", "int", "8", "name", "char", "10"};
            megatron.createRelation(relation);
        }
        break;
        case 4:{
            vector<string> relation = {"Student","15","miki"};
            megatron.insertRecord(relation);
        }
        break;
        case 5:
            readFile();
        break;
        case 6:
            cout << "Consulta: "<<endl;
        break;
        case 7:
            cout << "format" << endl;
        break;
        case 8:
            megatron.printInfo();
        break;
        case 9:
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