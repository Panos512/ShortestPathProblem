#include "graphLibrary.hpp"

uint32_t graphLibrary::binarySearch(uint32_t* array, int dim, uint32_t id) {
	int first = 0, middle = dim / 2;

	while (first <= dim) {
		if (array[middle] < id)
			first = middle + 1;
		else if (array[middle] == id)
			return array[middle];
		else
			dim = middle - 1;
		middle = (first + dim) / 2;
	}

	return UINT32_MAX;
}
