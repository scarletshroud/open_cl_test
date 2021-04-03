__kernel void MultiplyKernel(
	__global const double* matrixA, 
	__global const double* matrixB, 
	__global double* matrixC,
	int m,
	int n,
	int k
) {
	int row = get_global_id(0);
	int col = get_global_id(1);

	if (row >= m || col >= k)
		return;

	for (int i = 0; i < n; i++) {
		matrixC[row * k + col] += matrixA[row * n + i] * matrixB[i * k + col];
	}
}
