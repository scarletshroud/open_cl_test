__kernel void MultiplyKernel(
	__global const double* matrixA, 
	__global const double* matrixB, 
	__global double* matrixC,
	int m,
	int n,
	int k
) {
	int col = get_global_id(1);
	int row = get_global_id(0);
	
	if (row >= m || col >= k)
		return; 
		
	double sum = 0.0f;
	
	for (int i = 0; i < n; i++) {
		sum += matrixA[row * n + i] * matrixB[i * k + col];
	}
	
	matrixC[row * k + col] = sum;
}