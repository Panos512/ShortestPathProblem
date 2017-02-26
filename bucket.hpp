#ifndef _BUCKET_HPP_
#define _BUCKET_HPP_

#include <stdint.h>

class Bucket {
private:
	int bucketNo;
	int currentNo;
	uint32_t* cells;
public:
	Bucket(int);
	~Bucket();
	bool emptyCell();
	bool insertIdSorted(uint32_t);
	void printBucket();
	void doubleCells();
	uint32_t getFirst();
	uint32_t lookupId(uint32_t);
};


#endif
