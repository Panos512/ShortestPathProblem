#include <iostream>
#include <cstdlib>
#include <cassert>
#include "HashTable.hpp"

HashTable::HashTable(int tablesize, int bucketsize, int ptr, int Round)
	: nodeCount(0), tableSize(tablesize), realTableSize(tablesize), bucketSize(bucketsize), pointer(ptr), round(Round) {

	assert(buckets = (Bucket**)malloc(sizeof(Bucket*) * tableSize));

	for (int i = 0; i < realTableSize; ++i)
		assert(buckets[i] = new Bucket(bucketSize));

}

HashTable::~HashTable() {
	for (int i = 0; i < realTableSize; ++i) {
		delete buckets[i];
		buckets[i] = NULL;
	}

	free(buckets);
	buckets = NULL;
}

void HashTable::setTableSize(int tableSize) {
	this->tableSize = tableSize;
}

int HashTable::getNodeCount() const {
	return nodeCount;
}

int HashTable::getTableSize() const {
	return tableSize;
}

int HashTable::getBucketSize() const {
	return bucketSize;
}

int HashTable::hashFunction(int round, uint32_t id) const {
	return id % ((1 << round) * tableSize);
}

void HashTable::increaseHashTable() {
	assert(buckets = (Bucket**)realloc(buckets,sizeof(Bucket*) * realTableSize));
	assert(buckets[realTableSize - 1] = new Bucket(bucketSize));
}

bool HashTable::insertId(const uint32_t id) {
	int toBePlaced = hashFunction(round, id) >= pointer ? hashFunction(round, id) : hashFunction(round + 1, id);

	nodeCount++;
	if (buckets[toBePlaced]->emptyCell() == true)	//There is place in bucket
		return buckets[toBePlaced]->insertIdSorted(id);
	else {
		buckets[toBePlaced]->doubleCells();	//Adding a new chain bucket
		buckets[toBePlaced]->insertIdSorted(id);	//Adding node in the right place
		realTableSize += 1;		
		increaseHashTable();
		splitBucket(pointer);			//Spliting the bucket where the pointer was
		if (pointer == realTableSize / 2) {	//Pointer ends up, reset back to start
			pointer = 0;
			round++;
		}
		else					//Or just increase pointer
			pointer++;

		return true;
	}
}

void HashTable::splitBucket(int toSplit) {
	Bucket* oldBucket = buckets[toSplit];
	uint32_t toAdd;

	buckets[toSplit] = new Bucket(bucketSize);

	while ((toAdd = oldBucket->getFirst()) != UINT32_MAX)
		if (!buckets[hashFunction(round+1, toAdd)]->insertIdSorted(toAdd)) {	//Case everything goes to the new bucket
			buckets[hashFunction(round+1, toAdd)]->doubleCells();
			buckets[hashFunction(round+1, toAdd)]->insertIdSorted(toAdd);
		}

	delete oldBucket;
	oldBucket = NULL;
}

uint32_t HashTable::lookupId(uint32_t id) const {
	return hashFunction(round, id) >= pointer ? buckets[hashFunction(round, id)]->lookupId(id) : buckets[hashFunction(round+1, id)]->lookupId(id);
}
