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
	
	int idlocal = get_local_id(0);
	int nlocal = get_local_size(0);
	__local double bufB[2000]; 
	
	double sum;
	
	for (int col = 0; col < matrixSize; col++) {
		sum = 0.0;
		
		for (int i = idlocal; i < matrixSize; i = i + nlocal) {
			bufB[i] = matrixB[col * matrixSize + i];
		}
		barrier(CLK_LOCAL_MEM_FENCE);
		
		for (int i = 0; i < matrixSize; i++) {
			sum += bufA[i] * bufB[i];
		}
		
		matrixC[row * matrixSize + col] = sum;
	}
}