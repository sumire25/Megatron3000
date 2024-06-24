//
// Created by sumire on 5/10/24.
//

#ifndef MEGATRON_H
#define MEGATRON_H

#include "Disk_Manager/DiskManager.h"
#include "Query_Processor/ExecutionEngine.h"
#include "Buffer_Manager/BufferManager.h"


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

  void createRelation(vector<string>& relation);
  void insertRecord(vector<string>& record);
	void printBlock(int& blockId);
  void selectRecord(vector<string>& record);
  void deleteRecord(vector<string>& record);

  /**
 * Imprime el contenido del bloque dado su identificador
 * @param numBlock: identificador del bloque
 * @author Todos
 */
  void leerBloque(int numBlock);// Deberia de retornar el contenido de un bloque, consultando al buffermanager
  /**
  * Escribe en el bloque cuyo identificador es dado
  * @param numBlock: identificador del bloque
  * @author Todos
  */
  void escribirBloque(int numBloque);

  /**
   * Libera un bloque
   * @param numBloque
   * @author Todos
   */
  void liberarBloque(int numBloque);
  /**
   * Imprime los cantidad de misses y hits
   * @author Todos
   */
  void mostrarContadores();
  void pinPage(int numBloque);
  void unpinPage(int numBloque);
  void print();
};



#endif //MEGATRON_H
