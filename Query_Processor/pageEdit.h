#ifndef PAGEEDIT_H
#define PAGEEDIT_H

#include <map>
#include <string>
#include <vector>
#include "../Util/myFunc.h"

#define FREESPACE_SIZE 3
#define PAGEID_SIZE 8
#define VAR_OFFSET_SIZE 3
#define VAR_LENGTH_SIZE 3
#define NUM_PAIRS_SIZE 3

#define NUM_RECORDS_SIZE 2

namespace pageEdit {
    //UNPACKED PAGE
    int getAndUpdateFreePage(std::string &page, int recordSize, bool isVar);
    void setNewPageHeader(std::string &page);
    void addNewPageToDirectory(std::string &page, const int PageID, const int freeSpace);
    int getTotalNumRecords( const std::string &page, int recordSize);
    void setNewUnpacked(std::string &page, int recordSize);
    void insertUnpacked(std::string &page, const std::string &record);
    //SLOTTED PAGE
    struct Cabecera;
    void writeHeader(std::ostringstream& outStream, int value, size_t size);
    std::string setNewSlotted(size_t blockSize);
    Cabecera leerCabecera(const std::string& data);
    std::string insertSlotted(const std::string& data, const std::string& registro);
}

#endif //PAGEEDIT_H