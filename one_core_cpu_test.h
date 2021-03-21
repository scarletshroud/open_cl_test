#ifndef _ONE_CORE_CPU_TEST_H_
#define _ONE_CORE_CPU_TEST_H_

#include <vector>

#include "answer.h"

typedef std::vector<float> matrix;

class CpuTest {
public:
	CpuTest(); 
	~CpuTest(); 

	void test(matrix& matrixA, matrix& matrixB, int rows, int cols, Answer& answer);

private:
	matrix m_matrixA; 
	matrix m_matrixB;
	matrix m_matrixC; 

	int m_matrix_size;

	matrix multiply(matrix& matrixA, matrix& matrixB, int rows, int cols);
};

#endif

