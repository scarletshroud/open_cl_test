#ifndef _HOST_H_
#define _HOST_H_

#include <CL/cl.hpp>

typedef std::vector<double> matrix; 

class Host {
public: 
	Host(); 
	~Host(); 

	int init(); 
	int testKernel(const char* kernelPath, int workItems, int workGroups, matrix& matrixA, matrix& matrixB, int matrixSize);

private:
	cl::Device m_device;

	int checkParams(matrix& matrixA, matrix& matrixB, int matrixSize);
};

#endif
