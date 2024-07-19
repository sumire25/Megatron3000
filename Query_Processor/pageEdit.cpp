//
// Created by msumi on 23/06/2024.
//

#include "pageEdit.h"

namespace pageEdit {
    int getAndUpdateFreePage(std::string &page, int recordSize, bool isVar) {
        //nroDePares(3) freeSpace(3) header(3)  size id size id size id &

        //definir el espacio necesario si pertenece a pagina de longitud variable o fija
        int neededSpace;
        if (isVar)
            neededSpace = recordSize + VAR_OFFSET_SIZE + VAR_LENGTH_SIZE;
        else
            neededSpace = recordSize + 1;

        // recorrer byte por byte la página
        int numPairs = std::stoi(page.substr(0,NUM_PAIRS_SIZE));
        std::cerr << endl << "Num Pairs: " << numPairs << endl;
        for (int i = 0; i < numPairs; i++) {
            int index = NUM_PAIRS_SIZE + i * (PAGEID_SIZE + FREESPACE_SIZE);

            int currFreeSpace = std::stoi(page.substr(index,FREESPACE_SIZE));
            int currPageID = std::stoi(page.substr(index + FREESPACE_SIZE,PAGEID_SIZE));


            if (currFreeSpace >= neededSpace) {
                int newFreeSpace = currFreeSpace - neededSpace;

                // redimensionar el tamaño al freeSpace
                std::string newFreeSpaceStr = myFunc::padString(std::to_string(newFreeSpace), FREESPACE_SIZE);
                page.replace(index, FREESPACE_SIZE, newFreeSpaceStr);

                return currPageID;
            }
        }
        return -1;
    }

    void setNewPageHeader(std::string &page) {
        page.replace(0,NUM_PAIRS_SIZE, myFunc::padString(std::to_string(0),NUM_PAIRS_SIZE));
    }

    void addNewPageToDirectory(std::string &page, const int PageID, const int freeSpace) {
        int numPairs = std::stoi(page.substr(0,NUM_PAIRS_SIZE));
        int index = NUM_PAIRS_SIZE + numPairs * (PAGEID_SIZE + FREESPACE_SIZE);

        if (index + PAGEID_SIZE + FREESPACE_SIZE < page.length()) {
            const std::string newPageStr = myFunc::padString(std::to_string(PageID), PAGEID_SIZE);
            const std::string newFreeSpaceStr = myFunc::padString(std::to_string(freeSpace), FREESPACE_SIZE);

            page.replace(index, FREESPACE_SIZE, newFreeSpaceStr);
            page.replace(index + FREESPACE_SIZE, PAGEID_SIZE, newPageStr);

            page.replace(0,NUM_PAIRS_SIZE, myFunc::padString(std::to_string(numPairs + 1), NUM_PAIRS_SIZE));
        }
    }

    int getTotalNumRecords(const std::string &page, int recordSize) {
        const int totalNumRecords = (int(page.length()) - NUM_RECORDS_SIZE - 1) / (recordSize + 1); // +1 por el bitmap
        return totalNumRecords;
    }

    void setNewUnpacked(std::string &page, int recordSize) {
        // string para numRecords
        const std::string numRecords = myFunc::padString(std::to_string(0),NUM_RECORDS_SIZE);
        page.replace(0,NUM_RECORDS_SIZE, numRecords);

        // calculando el nro de registros segun recordSize y añadiendo el bitmap
        int totalNumRecords = getTotalNumRecords(page, recordSize);
        page.replace(NUM_RECORDS_SIZE, totalNumRecords, totalNumRecords, '0');
        page.replace(NUM_RECORDS_SIZE + totalNumRecords, 1, "&"); // separadorxc
    }
    //ERROR IN LAST BIT
    int insertUnpacked(std::string &page, const std::string &record) {
        const int recordSize = static_cast<int>(record.length());
        const int totalNumRecords = getTotalNumRecords(page, recordSize);
        const int numRecords = std::stoi(page.substr(0,NUM_RECORDS_SIZE));
        //nroDeRegistros(2) bitmap(1 por registro)
        int headerSize = NUM_RECORDS_SIZE + totalNumRecords + 1;
        for (int i = NUM_RECORDS_SIZE; page[i] != '&'; ++i) {
            if (page[i] == '0') {
                page.replace(i, 1, "1");
                const int index = (i - NUM_RECORDS_SIZE) * (recordSize);
                page.replace(headerSize + index, recordSize, record);
                // incrementando el nro de registros
                page.replace(0,NUM_RECORDS_SIZE, myFunc::padString(std::to_string(numRecords + 1),NUM_RECORDS_SIZE));
                return i - NUM_RECORDS_SIZE;
            }
        }
        std::cerr << "no hay espacio suficiente en la página" << std::endl;
        return -1;
    }

    //SLOTTED PAGE//

    struct Cabecera {
        size_t numRegistros;
        size_t finFreeSpace;
        std::vector<size_t> offsets;
        std::vector<size_t> longitudes;
    };

    // Suponiendo que writeHeader es una función que escribe un valor de tamaño fijo en un flujo
    void writeHeader(std::ostringstream &outStream, int value, size_t size) {
        std::string strValue = std::to_string(value);
        size_t fillSize = size - strValue.size();
        outStream << std::string(fillSize, '-') << strValue; // Rellena con '-' y luego añade el número
    }

    // Función para inicializar el bloque
    std::string setNewSlotted(size_t blockSize) {
        std::ostringstream outStream;

        // Escribir número de registros (0) y final del espacio libre (blockSize) en la cabecera
        writeHeader(outStream, 0, NUM_RECORDS_SIZE); // Número de registros
        writeHeader(outStream, blockSize, VAR_OFFSET_SIZE); // Final del espacio libre

        // Rellenar el bloque con '-' para representar bytes vacíos
        outStream << std::string(blockSize - (NUM_RECORDS_SIZE + VAR_OFFSET_SIZE), '-');
        // Restamos 6 para considerar los 6 bytes de la cabecera

        return outStream.str();
    }

    Cabecera leerCabecera(const std::string &data) {
        Cabecera cabecera;

        if (!data.empty()) {
            std::string line = data.substr(0, NUM_RECORDS_SIZE + VAR_OFFSET_SIZE); // leer los primeros 6 caracteres
            // Convertir los caracteres '-' a '0' para facilitar la conversión a número
            std::replace(line.begin(), line.end(), '-', ' ');

            cabecera.numRegistros = std::stoi(line.substr(0, NUM_RECORDS_SIZE));
            cabecera.finFreeSpace = std::stoi(line.substr(NUM_RECORDS_SIZE, VAR_OFFSET_SIZE));

            // Leer offsets y longitudes si hay registros
            if (cabecera.numRegistros > 0) {
                size_t offsetStart = NUM_RECORDS_SIZE + VAR_OFFSET_SIZE;
                // Posición donde comienzan los offsets en la cadena
                size_t recordInfoLength = VAR_OFFSET_SIZE + VAR_LENGTH_SIZE;
                // Tamaño en caracteres para cada conjunto de offset y longitud

                for (size_t i = 0; i < cabecera.numRegistros; ++i) {
                    std::string offsetStr = data.substr(offsetStart + i * recordInfoLength, VAR_OFFSET_SIZE);
                    std::string lengthStr = data.substr(offsetStart + i * recordInfoLength + VAR_OFFSET_SIZE,
                                                        VAR_LENGTH_SIZE);
                    std::replace(offsetStr.begin(), offsetStr.end(), '-', '0');
                    std::replace(lengthStr.begin(), lengthStr.end(), '-', '0');
                    size_t offset = std::stoi(offsetStr);
                    size_t length = std::stoi(lengthStr);
                    cabecera.offsets.push_back(offset);
                    cabecera.longitudes.push_back(length);
                }
            }
        } else {
            std::cerr << "La cadena de datos está vacía.\n";
        }

        return cabecera;
    }

    std::string insertSlotted(const std::string &data, const std::string &registro) {
        Cabecera cabecera = leerCabecera(data);

        // Verificar si hay espacio suficiente
        if ((cabecera.finFreeSpace - (cabecera.numRegistros * (VAR_OFFSET_SIZE + VAR_LENGTH_SIZE) + (
                                          NUM_RECORDS_SIZE + VAR_OFFSET_SIZE))) < registro.size()) {
            std::cerr << "No hay suficiente espacio para agregar el registro.\n";
            return data;
        }

        size_t posicion = cabecera.finFreeSpace - registro.size();
        std::ostringstream outStream;

        // Reescribir la cabecera con los datos actualizados
        cabecera.numRegistros++;
        cabecera.finFreeSpace = posicion;

        outStream << std::setw(NUM_RECORDS_SIZE) << std::setfill('-') << cabecera.numRegistros;
        outStream << std::setw(VAR_OFFSET_SIZE) << std::setfill('-') << cabecera.finFreeSpace;

        // Agregar el offset y longitud del nuevo registro
        cabecera.offsets.push_back(posicion + 1);
        cabecera.longitudes.push_back(registro.size());

        for (size_t i = 0; i < cabecera.numRegistros; ++i) {
            outStream << std::setw(VAR_OFFSET_SIZE) << std::setfill('-') << cabecera.offsets[i];
            outStream << std::setw(VAR_LENGTH_SIZE) << std::setfill('-') << cabecera.longitudes[i];
        }

        // Calcular el tamaño de la cabecera
        size_t cabeceraSize = (NUM_RECORDS_SIZE + VAR_OFFSET_SIZE) + cabecera.numRegistros * (
                                  VAR_OFFSET_SIZE + VAR_LENGTH_SIZE);

        // Construir newData con la cabecera actualizada y los registros existentes
        std::string newData = outStream.str();

        // Añadir el resto de los datos (después de la cabecera y registros existentes)
        newData += std::string(data.begin() + cabeceraSize, data.end());

        // Reemplazar el registro en la posición adecuada
        newData.replace(posicion, registro.size(), registro);

        return newData;
    }

    string getRecord(string &data, int slotnum, int recordSize) {
        int numRecords = getTotalNumRecords(data, recordSize);
        if (slotnum >= numRecords) {
            std::cerr << "No existe el registro en la página.\n";
            return "";
        }
        return data.substr(NUM_RECORDS_SIZE+numRecords+1 + slotnum*recordSize, recordSize);
    }
}
