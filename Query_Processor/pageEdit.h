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
#define SLOTNUM_SIZE 3
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
    /**
   * Obtiene y actualiza la página libre que tiene espacio suficiente para un registro.
   * @param page: referencia a la cadena que representa la página.
   * @param recordSize: tamaño del registro.
   * @param isVar: booleano que indica si el registro es de longitud variable.
   * @return ID de la página libre o -1 si no hay espacio suficiente.
   */
    int getAndUpdateFreePage(std::string &page, int recordSize, bool isVar);

 /**
   * Establece un nuevo encabezado en la página.
   * @param page: referencia a la cadena que representa la página.
   */
    void setNewPageHeader(std::string &page);

 /**
    * Agrega una nueva página al directorio.
    * @param page: referencia a la cadena que representa la página.
    * @param PageID: ID de la nueva página.
    * @param freeSpace: espacio libre en la nueva página.
    */
    void addNewPageToDirectory(std::string &page, const int PageID, const int freeSpace);
    // UNPACKED PAGE
    /**
     *
     * @param page una página de longitud fija
     * @param recordSize el tamaño fijo que fué designado esa página
     * @return el nro total de registros que puede tener esta página si está llena
     */
    int getTotalNumRecords( const std::string &page, int recordSize);

    /**
     * establece "configuración" de una página de longitud fija dado un tamaño fijo asignado
     * @param page una página que será configurada a longitud fija
     * @param recordSize el tamaño fijo que vamos a determinar para la página
     *
     */
    void setNewUnpacked(std::string &page, int recordSize);

    /**
     * inserta un registro ya formateado para longitud fija
     * @param page una página de longitud fija
     * @param record el registro ya configurado a longitud fija que se quiere insertar
     * @return slot number in page
     * @author Alonso
     */
    int insertUnpacked(std::string &page, const std::string &record);


    //SLOTTED PAGE
    /**
    * Estructura que representa la cabecera de una página slotted.
    * @author Suni Yanira
    */
    struct Cabecera;

    /**
     * Escribe un valor en la cabecera de una página con un tamaño fijo.
     * @param outStream: flujo de salida para escribir.
     * @param value: valor a escribir.
     * @param size: tamaño del valor a escribir.
     * @author Suni Yanira
     */
    void writeHeader(std::ostringstream& outStream, int value, size_t size);

 /**
  * Inicializa un bloque nuevo con formato slotted page.
  * @param blockSize: tamaño del bloque.
  * @return cadena que representa el bloque inicializado.
  * @author Suni Yanira
  */
    std::string setNewSlotted(size_t blockSize);

 /**
    * Lee la cabecera de una página slotted.
    * @param data: cadena que representa la página.
    * @return estructura Cabecera que contiene los datos de la cabecera.
    * @author Suni Yanira
    */
    Cabecera leerCabecera(const std::string& data);

 /**
 * Inserta un registro en una página slotted.
 * @param data: cadena que representa la página.
 * @param registro: cadena que representa el nuevo registro.
 * @return cadena actualizada que representa la página con el nuevo registro.
 * @author Suni Yanira
 */
    std::string insertSlotted(const std::string& data, const std::string& registro); //inserta un registro de longitud variable al bloque
 string selectRecordUnpacked(string& data, int slotnum, int recordSize);
 void deleteRecordUnpacked(string& data, int slotnum, int recordSize);

 int insertSlotted(std::string& data, const std::string& registro);
 std::string obtenerContenidoRegistro(const std::string& data, size_t numRegistro);
 std::string eliminarRegistro(std::string data, size_t numRegistro);
 void updatePageFreeSpaceFromPageHeader(std::string &pageHeader, int pageID, int newFreeSpace);

}

#endif //PAGEEDIT_H
