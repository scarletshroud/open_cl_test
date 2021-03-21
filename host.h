#ifndef _HOST_H_
#define _HOST_H_

#include <CL/cl.hpp>
#include "answer.h"

typedef std::vector<float> matrix;

class Host {
public:
	Host();
	~Host();

	int init();
	int transposeMatrix(const char* kernelPath, matrix& matr, matrix& transposedMatrix, int m, int n);
	int multiplyMatrices(const char* kernelPath, int workItems, int workGroups, matrix& matrixA, matrix& matrixB, int m, int n, int k, Answer& answer);

private:
	cl::Device m_device;

	int validateParams(matrix& matrixA, matrix& matrixB);
	cl::Program buildProgramOnDevice(const char* kernelPath, cl::Context& context, std::vector<cl::Device>& contextDevices);
};

#endif
