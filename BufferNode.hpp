#ifndef __BUFFERNODE_HPP__
#define __BUFFERNODE_HPP__

#define NEIGHBOUR_SIZE 50

#include <stdint.h>

class BufferNode {
private:
	uint32_t nodeIds[NEIGHBOUR_SIZE];
	uint32_t propertyIds[NEIGHBOUR_SIZE];
	int nextAvailable;
	int nextOffset;
public:
	uint32_t getNodeIdInArray(int);
	uint32_t getPropertyInArray(int);
	int getNextAvailable();
	void setNextAvailable(int);
	int getNextOffset();
	void setNextOffset(int);	
	void initialize();
	void addNodeId(uint32_t,uint32_t);
};


#endif
