//
// Created by msumi on 31/05/2024.
//

#include "../Buffer_Manager/Page.h"

#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H



class BufferPool {
private:
	Page* framelist; // lista de frames
public:
	BufferPool();
	~BufferPool();
	/**
	 * Obtiene la direccion de un frame en el buffer
	 * @param frameId: id del frame
	 * @return direccion del frame en el buffer
	 * @author Todos
	 */
	Page* getFrameDirection(int frameId);
};



#endif //BUFFERPOOL_H
