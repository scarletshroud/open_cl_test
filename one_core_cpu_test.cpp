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

int CpuTest::init(matrix& matrixA, matrix& matrixB, matrix& matrixC, int size) {
	
	if (matrixA.size() != matrixB.size()) {
		std::cout << "One Core CPU Test: The number of rows of matrix A is not equal to the number of columns of matrix B";
		return -1;
	}

	m_matrixA = matrixA;
	m_matrixB = matrixB;
	m_matrixC = matrixC; 

	m_matrix_size = size; 

	return 0;
}

void CpuTest::test() {
	auto start_time = std::chrono::high_resolution_clock::now();

	std::cout << "Matrix multiplication on CPU started..." << std::endl;

	multiply(); 

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	std::cout << std::endl << "-----------Matrix-Multiplication-Is-Successful-----------" << std::endl;
	std::cout << "Computing Device: CPU" << std::endl; 
	std::cout << "Matrix Size: " << m_matrix_size << std::endl;
	std::cout << "Compution time: " << duration << "ms" << std::endl;
	std::cout << "---------------------------------------------------------" << "\n\n";
}

void CpuTest::multiply() {
	for (size_t i = 0; i < m_matrix_size; ++i) {
		for (size_t j = 0; j < m_matrix_size; ++j) {
			m_matrixC[i * m_matrix_size + j] = 0;
			for (size_t k = 0; k < m_matrix_size; ++k) {
				m_matrixC[i * m_matrix_size + j] += m_matrixA[i * m_matrix_size + k] * m_matrixB[k * m_matrix_size + j];
			}
		}
	}
}