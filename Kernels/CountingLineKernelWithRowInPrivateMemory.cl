__kernel void MultiplyKernel(
	__global const double* matrixA, 
	__global const double* matrixB, 
	__global double* matrixC, 
	int matrixSize
) {
	int row = get_global_id(0);
	
	double bufA[2000];
	
	for (int i = 0; i < matrixSize; i++) {
		bufA[i] = matrixA[row * matrixSize + i];
	}
	
	double sum;
	
	for (int col = 0; col < matrixSize; col++) {
		sum = 0.0;
		
		for (int i = 0; i < matrixSize; i++) {
			sum += bufA[i] * matrixB[col * matrixSize + i];
		}
		
		matrixC[row * matrixSize + col] = sum;
	}
}