//
// Created by sumire on 5/10/24.
//

#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <iostream>
#include <unordered_map>

#include "../Util/myFunc.h"
using namespace std;

#define LL static_cast<long long>


class DiskManager {
private:
    string diskConfig;//ruta del archivo de configuracion del disco
    int plattes;
    int surfacesXplat;
    int tracksXsurf;
    int blocksXtrack;
    int bytesXblock;
    int bytesXsector;
    long long int totalSpace;
    long long int freeSpace;
    unordered_map<int, string> blockMaps;//no se hacen muchas reservas de bloques nuevos(podria eliminarse)

    //Guarda el bitmap de los bloques de un track
    void saveBlockMap(const int& track);
    void loadBlockMap(const int& track);
    void createBlockMap(const int& track);
    bool isBlockFree(const int& track, const int& blockId);
    void setBlockUsed(const int& track, const int& blockId);
    string blockfileFromId(const int &blockId);
public:
    /**
    * @brief Reserva un bloque aleatorio del disco
        * @return Identificador del bloque reservado
    * @author Marko
    */
    int allocRandomBlock();
    /**
    * @brief Reserva un bloque cercano al headerPage de un File
        * @param headerPage Identificador del headerPage de algun File
        * @return Identificador del bloque reservado
    * @author Marko
    */
    int allocNextBlock(const int & headerPage);
    /**
    * @brief Lee un bloque del disco
        * @param blockId Identificador del bloque a leer
        * @return Contenido leido del bloque
    * @author Marko
    */
    string readBlock(const int& blockId);
    /**
    * @brief Escribe en un bloque del disco
        * @param blockId Identificador del bloque donde escribir
        * @param content Contenido a escribir en el bloque
    * @author Marko
    */
    void writeBlock(const int &blockId, const string &content);
    /**
    * @brief Configura el disco y guarda la configuracion en un archivo
        * @param measures Arreglo con las medidas del disco
    * @author Marko
    */
    void setDisk(int* measures);
    /**
    * @brief (NOT_IMPLEMENTED): Carga la configuracion del disco, y la informacion del sgdb
    * @author
    */
    void loadfromDisk();
    /**
    * @brief Imprime configuracion del disco
    * @author Marko
    */
    void printInfo();
};



#endif //DISKMANAGER_H
