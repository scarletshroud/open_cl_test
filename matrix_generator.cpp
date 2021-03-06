#include "matrix_generator.h"

std::vector<double> generateMatrix(const size_t size) {
	std::vector<double> matrix(size * size);
	const size_t depth = 100;

	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			matrix[i * size + j] = (double)(rand()) / RAND_MAX * depth;
			//matrix[i * size + j] = 1;
		}
	}

	return matrix;
}