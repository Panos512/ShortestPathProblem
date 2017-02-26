#include <stdio.h>
#include "IndexNode.hpp"


int IndexNode::getOffsetFirst() {
	return offsetFirst;
}

void IndexNode::setOffsetFirst(int offsetFirst) {
	this->offsetFirst = offsetFirst;
}

int IndexNode::getOffsetLast() {
	return offsetLast;
}

void IndexNode::setOffsetLast(int offsetLast) {
	this->offsetLast = offsetLast;
}


bool IndexNode::lookUp(uint32_t nodeId) {
	if (ht == NULL) {
		ht = new HashTable(4, 10);
		return false;
	}

	return ht->lookupId(nodeId) == nodeId;
}

void IndexNode::insertId(uint32_t nodeId) {
	ht->insertId(nodeId);
}

void IndexNode::initialize() {
	offsetFirst = -1;
	offsetLast = -1;
	ht = NULL;
}

void IndexNode::freeMemory() {
	if (ht != NULL)
		delete ht;
}
