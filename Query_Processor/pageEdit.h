#ifndef PAGEEDIT_H
#define PAGEEDIT_H

#include <map>
#include <string>
#include <vector>
#include "../Util/myFunc.h"

#define NUM_RECORDS_SIZE 2

#define NUM_PAIRS_SIZE 3
#define FREESPACE_SIZE 3
#define PAGEID_SIZE 8
//offset y length de slottedPage
#define VAR_OFFSET_SIZE 3
#define VAR_LENGTH_SIZE 3
//offset y length de registros variables
#define OFFSET_SIZE 2
#define LENGTH_SIZE 2

namespace pageEdit {
    /**
     *@author Chullunquia Alonso
     */
    // HEADER PAGE
    int getAndUpdateFreePage(std::string &page, int recordSize, bool isVar);
    void setNewPageHeader(std::string &page);
    void addNewPageToDirectory(std::string &page, const int PageID, const int freeSpace);
    // UNPACKED PAGE
    int getTotalNumRecords( const std::string &page, int recordSize);
    void setNewUnpacked(std::string &page, int recordSize);
    void insertUnpacked(std::string &page, const std::string &record);


    /**
     *@author Suni Yanira
     */
    //SLOTTED PAGE
    struct Cabecera; //Se usa esta structurra para poder acceder a la cabecera del bloque
    void writeHeader(std::ostringstream& outStream, int value, size_t size); //se usa para escribir el header del bloque
    std::string setNewSlotted(size_t blockSize); //Inicializa el formato de un nuevo bloque con la estructura del slotted page
    Cabecera leerCabecera(const std::string& data); //Nos permite leer el bloque y extraer la cabecera en un struct Cabecera
    std::string insertSlotted(const std::string& data, const std::string& registro); //inserta un registro de longitud variable al bloque
}

#endif //PAGEEDIT_H
