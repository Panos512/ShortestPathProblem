#ifndef __INDEXNODE_HPP__
#define __INDEXNODE_HPP__

#include <stdint.h>
#include "HashTable.hpp"

class IndexNode {
private:
	int offsetFirst;
	int offsetLast;
	HashTable* ht;
public:
	int getOffsetFirst();
	void setOffsetFirst(int);
	int getOffsetLast();
	void setOffsetLast(int);
	bool lookUp(uint32_t);
	void insertId(uint32_t);
	void initialize();
	void freeMemory();
};


#endif
