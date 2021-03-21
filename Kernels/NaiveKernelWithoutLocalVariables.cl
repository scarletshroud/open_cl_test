__kernel void MultiplyKernel(
	__global const float* matrixA, 
	__global const float* matrixB, 
	__global float* matrixC,
	int matrixSize
) {
	int row = get_global_id(1);
	int col = get_global_id(0);

	for (int i = 0; i < matrixSize; i++) {
		matrixC[row * matrixSize + col] += matrixA[row * matrixSize + i] * matrixB[i * matrixSize + col];
	}
}
