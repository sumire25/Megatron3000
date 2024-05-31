//
// Created by msumi on 20/05/2024.
//

#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "BufferPool.h"
#include "../Storage_Manager/DiskManager.h"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>

/**
 * Gestiona el buffer, el cual es un conjunto de frames en memoria principal
 */
class BufferManager {
private:
	DiskManager* diskManRef; //Referencia al disk manager
	//key: pageId, value: <frameId, dirtyBit, pinCount>
	unordered_map<int,tuple<int, bool, int>> pageTable;
	list<int> LRUqueue; // cola de frames (unpinned) segun su uso reciente
	queue<int> freeFrames; // cola de frames libres
	BufferPool buffPool; // instancia del buffer pool
	int numFrames; // numero de frames
	int bufferSize; // tamaño del buffer
	int missCount; // contador de misses
	int hitCount; // contador de hits

	/**
 * Libera el frame que contiene a la pagina, escribe en disco si hay cambios
 * @param pageId: id de la pagina
 * @author Todos
 */
	void flushPage(int pageId);
	/**
 * Verifica si la pagina esta en el buffer, incrementa el pincount
 * @param pageId: id de la pagina
 * @return true si se pudo pinear la pagina, false en caso contrario
 * @author Todos
 */
	bool pinPage(int pageId);
public:
	BufferManager();
	/**
	 * Establece la conexion con el disk manager
	 * @param diskManRef: referencia al disk manager
	 * @author Todos
	 */
	void setDiskManRef(DiskManager* diskManRef);//setea la referencia al disk manager
	/**
	 * Obtiene el contenido de una pagina en el buffer
	 * @param pageId: id de la pagina
	 * @return referencia a la pagina en el buffer
	 * @author Todos
	 */
	Page* getPage(int pageId);
	/**
	 * Decrementa el pincount
	 * @param pageId: id de la pagina
	 * @author Todos
	 */
	void unpinPage(int pageId);
	/**
	 * Marca el dirty flag de la pagina
	 * @param pageId: id de la pagina
	 * @author Todos
	 */
	void setDirtyFlag(int pageId);
	/**
	 * Obtiene el contador de misses
	 * @return contador de misses
	 * @author Todos
	 */
	int getMissCount();
	/**
	 * Obtiene el contador de hits
	 * @return contador de hits
	 * @author Todos
	 */
	int getHitcount();
	/**
	 * Imprime la pageTable
	 * @author Todos
	 */
	void printPageTable();
	/**
	* Imprime la LRUqueue
	* @author Todos
	*/
	void printLRUqueue();
};



#endif //BUFFERMANAGER_H
