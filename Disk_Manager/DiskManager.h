#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <iostream>

#include "../Util/myFunc.h"
using namespace std;

#define LL static_cast<long long>

//Se encarga de la escritura y lectura del disco, mapea cada blockId a sus sectores en disco
class DiskManager {
private:
    //Datos que usa la funcion firstSectorFileFromId
    //para mapear cada blockId con el primer sector que contiene
    int plattes;
    int surfacesXplat;
    int tracksXsurf;
    int blocksXtrack;
    int bytesXblock;
    int bytesXsector;
    long long int totalSpace;
    long long int freeSpace;
    /**
     * @brief Crea el bitmap del pagedirectory y los guarda en un track
     * @author Marko
     */
    void createFreeBlockMap(const int& track);
    /**
     * @brief Verifica que ya exista un bitmap
     * @author Marko
     */
    bool existFreeBlockMap(const int& track);
    /**
     * @brief setea el bit correspondiente al bloque usado
     * @author Marko
     */
    void setBlockUsed(const int& track, const int& blockId);
    /**
     * @brief Obtiene el freeblockmap de un cilindro
     * @author Marko
     */
    string getFreeBlockMap(const int& track);
    /**
    * @brief Genera el path del primer sector sobre el cual esta algun bloque
        * @param blockId Identificador del bloque
        * @return "track/plate_surface_sector"
    * @author Marko
    */
    string firstSectorFileFromId(const int &blockId);
    /**
    * @brief Genera el los archivos correspondientes para cada bloque, y sus sectores
        * @param blockId Identificador del bloque
    * @author Marko
    */
    void createBlockFile(const int& blockId);
    /**
    * @brief Modifica el path al siguiente sector adyacente
        * @param sectorPath Path del sector
    * @author Marko
    */
    void incrementSectorPath(string& sectorPath);
public:
    /**
    * @brief Reserva un bloque aleatorio del disco (usarse solo para el headerPage de un File, al crearse una nueva relacion)
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
        * @return Contenido leido del bloque: string[bytesXblock]
    * @author Marko
    */
    string readBlock(const int& blockId);
    /**
    * @brief Escribe en un bloque del disco
        * @param blockId Identificador del bloque donde escribir
        * @param content Contenido a escribir en el bloque: string[bytesXblock]
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
    * @brief Carga la configuracion del disco, y la informacion del sgdb
    * @author Marko
    */
    void loadfromDisk();
    /**
    * @brief Imprime configuracion del disco
    * @author Marko
    */
    void printInfo();
};



#endif //DISKMANAGER_H
