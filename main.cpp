#include <fstream>
#include <iostream>
#include "Megatron.h"

void displayMenu();
void handleChoice(int choice);
void readFile(string &filename);

void writeTable(string table, string scheme) {
    // Abrir el archivo de salida
    ofstream schemeFile("../Data/scheme.txt", ios::app);
    if (!schemeFile.is_open()) {
        cerr << "Error al abrir el archivo scheme.txt." << endl;
    }
    schemeFile<<scheme<<endl;
    schemeFile.close();
    //crear el archivo de la relacion
    ofstream relationFile("../Data/"+table+".txt", ios::app);
    if (!relationFile.is_open())
        cerr << "Error creando el archivo de la tabla: " << table <<endl;
    relationFile.close();
}

void writeRegister(string table, string row) {
    // Abrir el archivo de salida
    ofstream tableFile("../Data/"+table+".txt", ios::app);
    if (!tableFile.is_open()) {
        cerr << "Error al abrir el archivo scheme.txt." << endl;
    }
    // Escribir los registros en el archivo de salida
    tableFile<<row<<endl;

    tableFile.close();
}

int main()
{
    Megatron megatron;
    megatron.load();
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
    cout << "1. Crear disco" << endl;   // crear archivos y setear data dictionary
    cout << "2. Leer archivo" << endl;  // leer todo o n registros

    // En qué plato, superficie, pista, sector y bloque
    // Al crear relacion definir longitud fija o varaiable
    cout << "3. Añadir nuevo registro" << endl; //
    cout << "4. Hacer una consulta" << endl;    //
        // eliminar registro

    cout << "5. Formatear Disco " << endl;  // Limpiar contenidos de los bloques
    cout << "6. Informacion del Disco " << endl;    // total, libre, ocupada, bloque, sector
    cout << "0. Cerrar" << endl;
    cout << "Seleccione una opcion: ";
}

void handleChoice(int choice) {
    switch(choice) {
        case 0:
            cout << "Cerrando Megatron3000." << endl;
            break;
        case 1:
            cout << "You selected Option 1" << endl;
            break;
        case 2: {
            string filename;
            cout << "Nombre del archivo csv: ";
            cin >> filename;
            readFile(filename);
            }
            break;
        case 3:
            cout << "andair registro\n";
            break;
        case 4: {
            string que;
            cout << "Consulta: ";
            getline(cin,que);
            cout << que << endl;
            getline(cin,que);
            cout << que << endl;
            // query.executeQuery(que);
            }
            break;
        case 5:
            cout << "format" << endl;
            break;
        case 6:
            cout << "info\n";
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

// Adicionar N registros de un *.csv
void readFile(string &filename) {
  ifstream file("../Data/"+filename+".csv");
  if (!file.is_open()) {
    cerr << "No se pudo abrir el archivo: " << filename+".csv" << endl;
  }

  string line, header, word;
  header = filename+"#";

  //Pedir tipos de los atributos
  getline(file, line);
  istringstream iss(line);
  while (getline(iss, word, '\t')) {
    header += word+"#";
    cout << "Ingrese el tipo de dato para " << word << ": ";
    cin >> word;
    header += word+"#";
  }
  header.pop_back();

  // Vector para almacenar los tamaños máximos de las columnas
  vector<int> maxColumnSizes;
  // Leer el archivo de entrada y encontrar los tamaños máximos de las columnas
  int column;
  while (getline(file, line)) {
    iss.clear();
    iss.str(line);
    column = 0;
    while (getline(iss, word, '\t')) {
      if (column >= maxColumnSizes.size()) {
        maxColumnSizes.push_back(word.size());
      } else {
        maxColumnSizes[column] = max(maxColumnSizes[column], static_cast<int>(word.size()));
      }
      ++column;
    }
  }
  // Cerrar el archivo de entrada
  file.close();

  // Agregar tamanos al header
  iss.clear();
  iss.str(header);
  header ="";
  column = 0;
  while (getline(iss, word, '#')) {
    if(column<2 || ((column-2) % 2 != 0))
      header += word+"#";
    else
      header += word+"#"+to_string(maxColumnSizes[(column-2) / 2])+"#";
    column++;
  }
  header.pop_back();
  // Escribir en disco
  writeTable(filename,header);

  // Volver a abrir el archivo de entrada
  file.open("../Data/"+filename+".csv");
  if (!file.is_open()) {
    cerr << "Error al abrir el archivo de entrada." << endl;
  }

  // Escribir los registros en el archivo de salida
  string row;
  getline(file, line);
  while (getline(file, line)) {
    iss.clear();
    iss.str(line);
    row = "";
    column = 0;
    while (getline(iss, word, '\t')) {
      // Añadir espacios en blanco al final de la palabra para igualar el tamaño máximo de la columna
      row += word;
      int padding = maxColumnSizes[column] - word.size();
      for (int i = 0; i < padding; ++i) {
        row += ' ';
      }
      ++column;
    }
    writeRegister(filename, row);
  }

  file.close();
}
