#include <iostream>
#include <cstdlib>
#include <cassert>
#include "bucket.hpp"
#include "graphLibrary.hpp"

Bucket::Bucket(int bucketsize) : bucketNo(bucketsize) {
	assert(cells = (uint32_t*) malloc(sizeof(uint32_t) * bucketNo));
	this->currentNo = 0;
}

Bucket::~Bucket() {
	free(cells);
	cells = NULL;
}

bool Bucket::emptyCell() {
	return currentNo != bucketNo;
}

bool Bucket::insertIdSorted(uint32_t id) {
	if (currentNo == bucketNo)
		return false;

	if (currentNo == 0 || cells[currentNo - 1] < id) {
		cells[currentNo++] = id;
		return true;
	}

	for (int i = 0; i < currentNo; ++i) {
		if (cells[i] > id) {
			uint32_t temp = cells[i];
			cells[i] = id;
			id = temp;
		}
	}
	cells[currentNo++] = id;

	return true;
}

void Bucket::printBucket() {
	std::cout << "Printing Bucket : \n\n";
	for (int i = 0; i < bucketNo; ++i)
		if (cells[i] != UINT32_MAX)
			std::cout << cells[i] << " ";
		else {
			std::cout << std::endl;
			return;
		}
}


void Bucket::doubleCells() {
	assert(cells = (uint32_t*) realloc(cells, sizeof(Bucket*) * bucketNo * 2));
	bucketNo *= 2;
}

uint32_t Bucket::getFirst() {	
	return currentNo == 0 ? UINT32_MAX : cells[--currentNo];
}

uint32_t Bucket::lookupId(uint32_t id) {
	return graphLibrary::binarySearch(cells, currentNo - 1, id);
}
