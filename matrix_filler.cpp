#include "matrix_filler.h"

void fillMatrixWithRandom(double* matrix, const size_t size, const size_t depth) {
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			//matrix[i * size + j] = ((double) (rand()) / RAND_MAX * depth);
			matrix[i * size + j] = 1;
		}
	}
}

void fillMatrixWithZeros(double* matrix, const size_t size) {
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			matrix[i * size + j] = 0;
		}
	}
}