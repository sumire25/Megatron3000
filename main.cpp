#include <fstream>
#include "Megatron.h"

void displayMenu();
void handleChoice(int choice);
void resetMegatron();

Megatron megatron;
int postid = 251;

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
    cout << "6. Consultar registro" << endl;
    cout << "7. Eliminar registro" << endl;
    cout << "8. Consulta rango" << endl;
    cout << "9. Reset Megatron and quit" << endl;
    cout << "10. mostrar arbol" << endl;
    cout << "0. Cerrar" << endl;
    cout << "Seleccione una opcion:" << endl;
}

void handleChoice(int choice) {
    switch (choice) {
        case 0:
            cout << "Cerrando Megatron3000." << endl;
            break;
        case 1: {
            //{plattes, surfacesXplat, tracksXsurf, sectorXtrack, bytesXsector, sectorXblock}
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
            vector<string> relation = {"Post", "Fixed", "postid", "int", "8", "userid", "int", "8", "pdate", "int", "8", "content", "char", "5"};
            megatron.createRelation(relation);
        }
        break;
        case 4: {

            megatron.insertRecord();
            postid++;
        }
        break;
        case 5:
            megatron.readFile();
            break;
        case 6: {
            megatron.selectRecord();
        }
        break;
        case 7: {
            megatron.deleteRecord();
        }
        break;
        case 8: {
            megatron.selectRangeRecords();
        }
        case 9: {
            megatron.resetMegatron();
            cout << "Megatron reseteado." << endl;
            break;
        }
        case 10: {
            megatron.printArbol();

        }
        break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

