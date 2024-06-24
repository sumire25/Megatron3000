
#ifndef HEADERPAGEFUNCTIONS_H
#define HEADERPAGEFUNCTIONS_H
#include <map>
#include <string>
#include <vector>
#include "../../Util/myFunc.h"

#define FREESPACE_SIZE 3
#define PAGEID_SIZE 8
#define VAR_OFFSET_SIZE 3
#define VAR_LENGTH_SIZE 3
#define NUM_PAIRS_SIZE 3

#define NUM_RECORDS_SIZE 2
namespace headerPageFunctions {
    inline int getAndUpdateFreePage(std::string &page, int recordSize, bool isVar) {
        //nroDePares(3) header(4) freeSpace(4) id size id size id size id &

        //definir el espacio necesario si pertenece a pagina de longitud variable o fija
        int neededSpace;
        if (isVar)
            neededSpace = recordSize + VAR_OFFSET_SIZE + VAR_LENGTH_SIZE;
        else
            neededSpace = recordSize;

        for (int i = 0; i < std::stoi(page.substr(0,NUM_PAIRS_SIZE)) ; i++) {
            int index = NUM_PAIRS_SIZE + (i)*(PAGEID_SIZE+FREESPACE_SIZE);

            int currFreeSpace = std::stoi(page.substr(index,FREESPACE_SIZE));
            int currPageID = std::stoi(page.substr(index + FREESPACE_SIZE,PAGEID_SIZE));


            if(currFreeSpace >= neededSpace) {

                int newFreeSpace = currFreeSpace - neededSpace;

                // redimensionar el tamaño al freeSpace
                std::string newFreeSpaceStr = myFunc::padString(std::to_string(newFreeSpace), FREESPACE_SIZE);
                page.replace(index, FREESPACE_SIZE,newFreeSpaceStr);

                return currPageID;

            }

        }
        return -1;
    }

    inline void addNewPageToDirectory(std::string &page, const int PageID, const int freeSpace) {

        int numPairs = std::stoi(page.substr(0,NUM_PAIRS_SIZE));
        int index = NUM_PAIRS_SIZE + numPairs*(PAGEID_SIZE+FREESPACE_SIZE);

        if (index+PAGEID_SIZE+FREESPACE_SIZE < page.length()) {
            const std::string newPageStr = myFunc::padString(std::to_string(PageID), PAGEID_SIZE);
            const std::string newFreeSpaceStr = myFunc::padString(std::to_string(freeSpace), FREESPACE_SIZE);

            page.replace(index, FREESPACE_SIZE, newFreeSpaceStr);
            page.replace(index + FREESPACE_SIZE, PAGEID_SIZE , newPageStr);

            page.replace(0,NUM_PAIRS_SIZE, myFunc::padString(std::to_string(numPairs+1), NUM_PAIRS_SIZE) );

        }
    }

    inline int getTotalNumRecords( const std::string &page, int recordSize) {
        const int totalNumRecords = (int(page.length()) - NUM_RECORDS_SIZE - 1) / (recordSize+1); // +1 por el bitmap
        return totalNumRecords;
    }

    inline void setNewPacked(std::string &page, int recordSize) {
        // NUM_REG , bitmap , 1 ,
        // string para numRecords
        const std::string numRecords = myFunc::padString(std::to_string(0),NUM_RECORDS_SIZE );
        page.replace(0,NUM_RECORDS_SIZE,numRecords);

        // calculando el nro de registros segun recordSize y añadiendo el bitmap
        int totalNumRecords = getTotalNumRecords(page, recordSize);
        page.replace(NUM_RECORDS_SIZE,totalNumRecords,totalNumRecords,'0');
        page.replace(NUM_RECORDS_SIZE+totalNumRecords,1,"&"); // separadorxc
    }

    inline void insertPacked(std::string &page, const std::string &record) {
        const int recordSize = static_cast<int>(record.length());
        const int totalNumRecords = getTotalNumRecords(page,recordSize);
        //nroDeRegistros(2) bitmap(1 por registro)
        int headerSize = NUM_RECORDS_SIZE + totalNumRecords + 1;
        for(int i = NUM_RECORDS_SIZE; page[i] != '&' ; ++i ) {
            if(page[i] == '0') {
                page.replace(i,1,"1");
                const int index = i - NUM_RECORDS_SIZE*(recordSize) ;
                page.replace(headerSize + index,recordSize,record);
                return;
            }
        }
        std::cerr << "no hay espacio suficiente en la página" << std::endl;
    }
}





#endif //HEADERPAGEFUNCTIONS_H
