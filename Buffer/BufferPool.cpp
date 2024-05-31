//
// Created by msumi on 31/05/2024.
//

#include "BufferPool.h"

BufferPool::BufferPool() {
	framelist = new Page[NUM_FRAMES];
}

BufferPool::~BufferPool() {
	delete[] framelist;
}

Page * BufferPool::getFrameDirection(int frameId) {
	return &framelist[frameId];
}
