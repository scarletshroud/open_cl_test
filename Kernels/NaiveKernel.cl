__kernel void MultiplyKernel(
	__global const double* matrixA, 
	__global const double* matrixB, 
	__global double* matrixC,
	int matrixSize
) {
	int row = get_global_id(1);
	int col = get_global_id(0);

	double sum = 0;
	for (int i = 0; i < matrixSize; i++) {
		sum += matrixA[row * matrixSize + i] * matrixB[i * matrixSize + col];
	}
	matrixC[row * matrixSize + col] = sum;
}