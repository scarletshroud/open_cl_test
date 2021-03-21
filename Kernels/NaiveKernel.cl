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

	double sum = 0.0f;
	
	if (row >= m && col >= k)
		return; 

	for (int i = 0; i < n; i++) {
		int offsetA = row * n + i;
		int offsetB = i * k + col;
		
		sum += matrixA[offsetA] * matrixB[offsetB];
	}
	
	matrixC[row * k + col] = sum;
}