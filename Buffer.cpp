#include <stdlib.h>
#include <iostream>
#include "Buffer.hpp"
#include "BufferNode.hpp"


Buffer::Buffer() {
	bufferNodes = (BufferNode*) malloc(sizeof(BufferNode) * BUFFER_SIZE);
	size = BUFFER_SIZE;
	nextAvailable = 0;
	for (int i = 0; i < size; i++)
		bufferNodes[i].initialize();
}

Buffer::~Buffer() {
	free(bufferNodes);
}

int Buffer::getSize() {
	return size;
}

int Buffer::getNextAvailable() {
	return nextAvailable;
}

void Buffer::setNextAvailable(int nextAvailable) {
	this->nextAvailable = nextAvailable;
} 

void Buffer::doubleBuffer() {
	bufferNodes = (BufferNode*) realloc(bufferNodes, sizeof(BufferNode) * size * 2);
	for (int i = size; i < size * 2; i++)
		bufferNodes[i].initialize();
	size <<= 1;
}

int Buffer::fetchNewBufferNode() {
	if (nextAvailable == size)
		doubleBuffer();

	return nextAvailable++;
}

BufferNode* Buffer::getBufferNodeByOffset(int offset) {
	return bufferNodes + offset;
}
