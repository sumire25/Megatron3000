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
   *
   * @param blockId muestra el contenido del bloque
   */
  // void printBlock(int& blockId);

  /**
 * Lee e imprime el contenido del bloque dado su identificador subiendolo a memoria si es necesario
  * Imprime info del BufferMan al momento
 * @param numBlock: identificador del bloque
 * @author Todos
 */
  void leerBloque(int numBlock);// Deberia de retornar el contenido de un bloque, consultando al buffermanager

  /**
  * Escribe en el bloque cuyo identificador es dado subiendo el bloque a memoria si es necesario.
  * Imprime info del BufferMan al momento
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

  /**
   * Fija una página desde BufferManager
   * @param numBloque identificador del bloque
   * @author  todos
   */
  void pinPage(int numBloque);

  /**
   * Remueve fijar de una página
   * @param numBloque identificador del bloque
   * @author  todos
   */
  void unpinPage(int numBloque);

  /**
   * Imprime la cola de solicitudes, page table, y el reemplazador
   * @author todos
   */
  void print();

  string selectPost(int postId);
};



#endif //MEGATRON_H
