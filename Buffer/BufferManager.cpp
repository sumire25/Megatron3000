//
// Created by msumi on 20/05/2024.
//

#include "BufferManager.h"

BufferManager::BufferManager() {
	this->numFrames = NUM_FRAMES;
	this->bufferSize = PAGE_SIZE * NUM_FRAMES;
	// incializar hit y miss count
	hitCount = 0;
	missCount = 0;
	//inicializar lista freeFrames
	int i;
	for(i=0; i<numFrames; i++) freeFrames.push(i);
}

BufferManager::~BufferManager() {
	for (const auto& entry : pageTable) {
		int key = entry.first;
		const tuple<int, bool, int>& value = entry.second;
		if(get<1>(value)) {
			Page* page = buffPool.getFrameDirection(get<0>(value));
			diskManRef->writeBlock(key, *(page->data));
		}
	}
}

void BufferManager::setDiskManRef(DiskManager *diskManRef) {
	this->diskManRef = diskManRef;
}

Page * BufferManager::getPage(int pageId) {
	// pinear pagina
	if(pinPage(pageId)) {// retornar direccion del frame que sostiene a la pagina
		return buffPool.getFrameDirection(get<0>(pageTable[pageId]));
	}
	return nullptr;
}

void BufferManager::flushPage(int pageId) { // recibira una pagina que esta en un frame
	if(get<2>(pageTable[pageId]) != 0) {
		cerr << "No se puede liberar la pagina " << pageId << " porque esta siendo usada" << endl;
		return;
	}
	if(get<1>(pageTable[pageId])) { // la escribira en disco si dirtyflag es true
		Page* page = buffPool.getFrameDirection(get<0>(pageTable[pageId]));
		diskManRef->writeBlock(pageId, *(page->data));
	}
	//liberar frame
	freeFrames.push(get<0>(pageTable[pageId]));// agregar frameId a la lista de frames libres
	pageTable.erase(pageId);// eliminar seguimiento de la pagina del pagetable
	LRUqueue.pop_front();// eliminar pagina de la cola LRU
	cerr<<"Flushing page: "<<pageId<<endl; // mensaje de depuracion
}

bool BufferManager::pinPage(int pageId) {
	if(pageTable.find(pageId) == pageTable.end()) // Si la pagina no esta en el BufferPool
	{
		if(freeFrames.size() == 0) { //Si no hay frames disponibles
			if(!LRUqueue.empty()) {
				int page = LRUqueue.front();
				flushPage(page);// liberamos el frame de la cabecera de la LRUqueue
				cerr<<"misscount ++"<<endl;
				missCount++;
			}
			else {
				cerr << "No hay frames disponibles" << endl;
				return 0;
			}
		}
		//reservar frame
		int freeFrame = freeFrames.front();
		freeFrames.pop();
		//escribir contenido del bloque en el frame
		*(buffPool.getFrameDirection(freeFrame)->data) = diskManRef->readBlock(pageId);
		//registrar en el pagetable
		pageTable[pageId] = make_tuple(freeFrame, false, 0);
	} else {
		if(get<2>(pageTable[pageId]) == 0) { // Si esta unpinned
			for (auto it = LRUqueue.begin(); it != LRUqueue.end(); ++it) {
				if (*it == pageId) {
					LRUqueue.erase(it); //lo retiramos del LRUqueue
					break;
				}
			}
		}
		cout<<"hitcount ++"<<endl;
		hitCount++;
	}
	get<2>(pageTable[pageId])++; //incrementar pincount
	return 1;
}

void BufferManager::unpinPage(int pageId) {
	if((--get<2>(pageTable[pageId])) == 0)// decrementar pincount y verificar si esta unpinned
		LRUqueue.push_back(pageId); //intrducir la pagina en LRU queue
}

void BufferManager::setDirtyFlag(int pageId) {
	get<1>(pageTable[pageId]) = true;
}

int BufferManager::getMissCount() {
	return missCount;
}

int BufferManager::getHitcount() {
	return hitCount;
}

void BufferManager::printPageTable() {
	cout << "\t----------------------------------------------" << endl;
	cout << "\t| Page ID | Frame ID | dirty bit | pin count |" << endl;
	for (const auto& entry : pageTable) {
		int key = entry.first;
		const tuple<int, bool, int>& value = entry.second;

		int firstElement = get<0>(value);
		int secondElement = get<1>(value);
		int thirdElement = get<2>(value);

		cout << "\t----------------------------------------------" << endl;
		cout << "\t|    " << key << "    |    " << firstElement << "     |     " << secondElement << "     |     " << thirdElement << "     |" << endl;
	}
	cout << "\t----------------------------------------------\n" << endl;
}

void BufferManager::printLRUqueue() {
	for (const int& item : LRUqueue) {
		cout << "| " << item << " | <- ";
	}
	cout << "end\n" << endl;
}
