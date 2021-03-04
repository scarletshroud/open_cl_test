#include "matrix_generator.h"

Matrix generateMatrix(const size_t size, const size_t depth) {
	Matrix matrix(size * size);

	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
		//	matrix[i * size + j] = (double)(rand()) / RAND_MAX * depth;
			matrix[i * size + j] = 1;
		}
	}

	return matrix;
}