__kernel void MultiplyKernel(
	__global const double* matrixA, 
	__global const double* matrixB, 
	__global double* matrixC,
	int matrixSize
) {
	int row = get_global_id(0);
	int col = get_global_id(1);

	for (int i = 0; i < matrixSize; i++) {
		matrixC[row * matrixSize + col] += matrixA[row * matrixSize + i] * matrixB[col * matrixSize + i];
	}
}
