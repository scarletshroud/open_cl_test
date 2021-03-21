#include "one_core_cpu_test.h"

#include <iostream>
#include <chrono>

CpuTest::CpuTest() {
	m_matrixA = matrix(0); 
	m_matrixB = matrix(0);
	m_matrixC = matrix(0);

	m_matrix_size = 0; 
}

CpuTest::~CpuTest() {

}

void CpuTest::test(matrix& matrixA, matrix& matrixB, int rows, int cols, Answer& answer) {
	auto start_time = std::chrono::high_resolution_clock::now();

	std::cout << "Matrix multiplication on CPU started..." << std::endl;

	
	answer.setData(multiply(matrixA, matrixB, rows, cols));

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	answer.setCorrect();
	answer.setExecutionTime(duration);
}

matrix CpuTest::multiply(matrix& matrixA, matrix& matrixB, int rows, int cols) {
	matrix c(rows * cols);

	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			c[i * rows + j] = 0;
			for (size_t k = 0; k < cols; ++k) {
				c[i * rows + j] += matrixA[i * rows + k] * matrixB[k * cols + j];
			}
		}
	}

	return c;
}