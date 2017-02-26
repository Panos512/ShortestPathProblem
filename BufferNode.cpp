#include "BufferNode.hpp"

uint32_t BufferNode::getNodeIdInArray(int pos) {
	return nodeIds[pos];
}

uint32_t BufferNode::getPropertyInArray(int pos) {
    return propertyIds[pos];
}

int BufferNode::getNextAvailable() {
	return nextAvailable;
}

void BufferNode::setNextAvailable(int nextAvailable) {
	this->nextAvailable = nextAvailable;
}

int BufferNode::getNextOffset() {
	return nextOffset;
}

void BufferNode::setNextOffset(int nextOffset) {
	this->nextOffset = nextOffset;
}

void BufferNode::initialize() {
	nextAvailable = 0;
	nextOffset = -1;
}

void BufferNode::addNodeId(uint32_t nodeId, uint32_t currentVersion) {
	nodeIds[nextAvailable] = nodeId;
	propertyIds[nextAvailable] = currentVersion;
	nextAvailable++;
}
