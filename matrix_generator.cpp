#include "matrix_generator.h"

std::vector<float> generateMatrix(const size_t size) {
	std::vector<float> matrix(size * size);
	const size_t depth = 100;

	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			matrix[i * size + j] = (float)(rand()) / RAND_MAX * depth;
		}
	}

	return matrix;
}