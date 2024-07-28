//
// Created by msumi on 20/05/2024.
//

#include "BufferManager.h"

BufferManager::BufferManager(int replacerType) {
	this->numFrames = NUM_FRAMES;
	this->bufferSize = PAGE_SIZE * NUM_FRAMES;
	// incializar hit y miss count
	hitCount = 0;
	missCount = 0;
	//inicializar frameInfo
	for(int i=0; i<numFrames; i++) frameInfo[i] = make_tuple(false, 0, false);
	//inicializar replacer
	if(replacerType == 2) replacer = new ClockReplacer(frameInfo, numFrames);
	else replacer = new LruReplacer(frameInfo, numFrames);
}

BufferManager::~BufferManager() {
	for (const auto& entry : pageTable) {
		int key = entry.first;
		int frameId = entry.second;
		if(get<0>(frameInfo[frameId])) {
			Page* page = buffPool.getFrameDirection(frameId);
			diskManRef->writeBlock(key, *(page->data));
		}
	}
}

void BufferManager::setDiskManRef(DiskManager *diskManRef) {
	this->diskManRef = diskManRef;
}

Page * BufferManager::getPage(int pageId) {
	return buffPool.getFrameDirection(pageTable[pageId]);
}

void BufferManager::writePage(int pageId) {
	Page* page = buffPool.getFrameDirection(pageTable[pageId]);
	diskManRef->writeBlock(pageId, *(page->data));
	cerr<<"Escribiendo pagina: "<<pageId<<endl;
}

bool BufferManager::flushPage(int pageId) {
	int frameId = pageTable[pageId];
	if(get<1>(frameInfo[frameId]) != 0) {// si la pagina esta pinned
		cerr << "No se puede liberar la pagina " << pageId << " porque esta siendo usada" << endl;
		return false;
	}
	if(get<0>(frameInfo[frameId])) {// la escribira en disco si dirtyflag es true
		/*int opc;
		cout<<"(flush)Escribir el contenido de la pagina "<<pageId<<" en disco? si(1), no(2)"<<endl;
		cin>>opc;
		if(opc == 2) return false;*/
		writePage(pageId);
	}
	pageTable.erase(pageId);// eliminar seguimiento de la pagina del pagetable
	cerr<<"Flushing page: "<<pageId<<endl;
	return true;
}

bool BufferManager::pinPage(int pageId, RequestType requestType) {
	int frameId;
	if(pageTable.find(pageId) == pageTable.end()) {// Si la pagina no esta en el BufferPool
		frameId = replacer->getVictim();//obtener el victimFrame
		if(frameId == -1) {// Si no hay frames disponibles
			cerr << "No hay frames disponibles" << endl;
			return false;
		}
		int victimPage = getPageidfromFrame(frameId);
		if(victimPage != -1) {// Si el victimFrame tiene una pagina
			if(!flushPage(victimPage)) {
				cerr << "Escoger otra victima" << endl;
				return false;
			}
		}
		//cargar la pagina en el frame y actualizar el pageTable
		pageTable[pageId] = frameId;
		frameInfo[frameId] = make_tuple(false, 0, false);
		*(buffPool.getFrameDirection(frameId)->data) = diskManRef->readBlock(pageId);
		missCount++;
	}
	else {// Si la pagina esta en el BufferPool
		frameId = pageTable[pageId];
		hitCount++;
	}
	//pinnear la pagina
	get<1>(frameInfo[pageTable[pageId]])++;
	requestQueue[frameId].push(requestType);
	if(requestQueue[frameId].size() == 1 && requestType==RequestType::WRITE) {
		setDirtyFlag(pageId);
	}
	replacer->handlePinning(frameId);
	return true;
}

int BufferManager::getPageidfromFrame(int frameId) {
	int victimPage = -1;
	for (const auto& entry : pageTable) {
		if(entry.second == frameId) {
			victimPage = entry.first;
			break;
		}
	}
	return victimPage;
}

void BufferManager::unpinPage(int pageId) {
	int frameId = pageTable[pageId];
	bool pinned = get<2>(frameInfo[frameId]);
	if(get<0>(frameInfo[frameId])) {// la escribira en disco si dirtyflag es true??
		/*int opc;
		cout<<"(unpin)Escribir el contenido de la pagina "<<pageId<<" en disco? si(1), no(2)"<<endl;
		cin>>opc;
		if(opc == 1) */{
			writePage(pageId);
			get<0>(frameInfo[frameId]) = false;
		}
	}
	requestQueue[frameId].pop(); //pop the request from the queue
	if(!requestQueue[frameId].empty() && requestQueue[frameId].front() == RequestType::WRITE) {
		setDirtyFlag(pageId);//set dirty flag if the next request is RequestType::WRITE
	}
	if(((--get<1>(frameInfo[pageTable[pageId]])) == 0) && !pinned)//si la pagina esta unpinned
		replacer->handleUnpinning(pageTable[pageId]);//actualizar el estado del frame en el reemplazador
}

void BufferManager::setDirtyFlag(int pageId) {
	get<0>(frameInfo[pageTable[pageId]]) = true;
}

int BufferManager::allocRandomBlock() {
	return diskManRef->allocRandomBlock();
}

int BufferManager::allocNextBlock(int &headerPage) {
	return diskManRef->allocNextBlock(headerPage);
}

int BufferManager::getMissCount() {
	return missCount;
}

int BufferManager::getHitcount() {
	return hitCount;
}

void BufferManager::printPageTable() {
	cout << "\t-------------------------------------------------------" << endl;
	cout << "\t| Page ID | Frame ID | dirty bit | pin count | pinned |" << endl;
	for (const auto& entry : pageTable) {
		int key = entry.first;
		int frameId = entry.second;

		bool dirtyBit = get<0>(frameInfo[frameId]);
		int pinCount = get<1>(frameInfo[frameId]);
		bool pinned = get<2>(frameInfo[frameId]);

		cout << "\t-------------------------------------------------------" << endl;
		cout << "\t|    " << key << "    |    " << frameId << "     |     " << dirtyBit << "     |     " << pinCount << "     |   " << pinned << "    |" << endl;
	}
	cout << "\t-------------------------------------------------------\n" << endl;
}

void BufferManager::printReplacer() {
	replacer->print();
}
void BufferManager::printRequestQueue() {
	for(int i = 0; i < numFrames; i++) {
		cout << "Frame " << i << ": ";
		queue<RequestType> tempQueue = requestQueue[i]; // Copy the queue to a temporary queue
		while(!tempQueue.empty()) {
			RequestType requestType = tempQueue.front();
			tempQueue.pop();
			if(requestType == RequestType::READ) {
				cout << "READ ";
			} else if(requestType == RequestType::WRITE) {
				cout << "WRITE ";
			}
		}
		cout << endl;
	}
}
void BufferManager::pinningPage(int pageId) {
	get<2>(frameInfo[pageTable[pageId]]) = true;
}

void BufferManager::unpinningPage(int pageId) {
	get<2>(frameInfo[pageTable[pageId]]) = false;
	if(get<1>(frameInfo[pageTable[pageId]]) == 0)
		replacer->handleUnpinning(pageTable[pageId]);
}
