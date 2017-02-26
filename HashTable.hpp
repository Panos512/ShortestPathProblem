#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_

#include <stdint.h>
#include "bucket.hpp"

class HashTable {
private:
	int nodeCount;
	int tableSize;
	int realTableSize;
	int bucketSize;
	int pointer;
	int round;
	Bucket** buckets;

public:
	HashTable(int,int,int = 0,int = 0);
	~HashTable();
	void setTableSize(int);
	int getNodeCount() const;
	int getTableSize() const;
	int getBucketSize() const;
	int hashFunction(int, uint32_t) const;
	bool insertId(const uint32_t);
	void increaseHashTable();
	void splitBucket(int);
	uint32_t lookupId(uint32_t) const;
};


#endif
