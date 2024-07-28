//
// Created by sumire on 5/10/24.
//

#ifndef MEGATRON_H
#define MEGATRON_H

#include "Disk_Manager/DiskManager.h"
#include "Query_Processor/ExecutionEngine.h"
#include "Buffer_Manager/BufferManager.h"


/**
* @author  Sumire Marko
*/

class Megatron {
private:
  DiskManager diskMan;
  BufferManager buffManager;
  ExecutionEngine excEngine;
public:
  Megatron();
  void setDisk(int* measures);
  void loadfromDisk();
  void printInfo();
  /**
   * Crea una relación en el disco y le asigana un page header
   * @param relation vector relación {nombre, tipo, atributo1, tipo1, longitud1, atributo2, tipo2, longitud2, ...}
   * @author Alonso
   */
  void createRelation(vector<string>& relation);
  /**
   * inserta un registro dado el formato de un vector de strings
   * @param record vector de strings que representa el registro {relName, valor1, valor2, ...}
   * @author Alonso
   */
  void insertRecord(vector<string>& record);
/**
* Lee un archivo csv y crea una relación y registros en base a los datos del archivo
* @author todos
*/
  void readFile();
  void selectRecord();
  void deleteRecord();
};



#endif //MEGATRON_H
