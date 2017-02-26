#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#define BUFFER_SIZE 1024

#include "BufferNode.hpp"

class Buffer {
private:
	BufferNode* bufferNodes;
	int size;
	int nextAvailable;
public:
	Buffer();
	~Buffer();
	BufferNode getBufferNode(int);
	int getSize();
	int getNextAvailable();
	void setNextAvailable(int);
	void doubleBuffer();
	int fetchNewBufferNode();
	BufferNode* getBufferNodeByOffset(int);
};


#endif
