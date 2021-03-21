#include "test_reader.h"

#include <fstream>

Test readTestFromFile(const char* path) {
	std::ifstream in(path);

	size_t m = 0;
	size_t n = 0;
	size_t k = 0;

	in >> m; 
	in >> n; 
	in >> k;

	std::vector<float> matrixA(m * n);
	for (size_t i = 0; i < m; ++i) {
		for (size_t j = 0; j < n; ++j) {
			in >> matrixA[i * n + j];
		}
	}

	std::vector<float> matrixB(n * k);
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < k; ++j) {
			in >> matrixB[i * k + j];
		}
	}

	std::vector<float> matrixC(m * k);
	for (size_t i = 0; i < m; ++i) {
		for (size_t j = 0; j < k; ++j) {
			in >> matrixC[i * k + j];
		}
	}

	in.close();

	return Test(matrixA, matrixB, matrixC, m, n, k);
}
