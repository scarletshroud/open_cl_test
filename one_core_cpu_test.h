#ifndef _ONE_CORE_CPU_TEST_H_
#define _ONE_CORE_CPU_TEST_H_

#include <vector>

typedef std::vector<double> matrix;

class CpuTest {
public:
	CpuTest(); 
	~CpuTest(); 
	
	int init(matrix& matrixA, matrix& matrixB, matrix& matrixC, int size);
	void test();

private:
	matrix m_matrixA; 
	matrix m_matrixB;
	matrix m_matrixC; 

	int m_matrix_size;

	void multiply();
};

#endif

