#ifndef _NAIVE_MULTIPLY_GPU_TEST_H_
#define _NAIVE_MULTIPLY_GPU_TEST_H_

#include <CL/cl.hpp>

typedef std::vector<double> matrix; 

class NaiveGpuTest {
public: 
	NaiveGpuTest(); 
	~NaiveGpuTest(); 

	int init(matrix& matrixA, matrix& matrixB, matrix& matrixC, int matrix_size); 
	int test(); 

private:
	cl::Device m_device;

	matrix m_matrixA; 
	matrix m_matrixB;
	matrix m_matrixC;

	int m_matrix_size; 
};

#endif
