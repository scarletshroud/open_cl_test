#define MAX_SIZE 300

__kernel void MultiplyKernel(
	__global const float* matrixA, 
	__global const float* matrixB, 
	__global float* matrixC, 
	int matrixSize
) {
	const int row = get_global_id(0);
	const int localCol = get_local_id(0);
	const int localSize = get_local_size(0);
	
	float bufA[MAX_SIZE];
	__local float bufB[MAX_SIZE];
	
	for (int i = 0; i < matrixSize; i++) {
			bufA[i] = matrixA[row * matrixSize + i];
	}
	
	float sum;

	for (int col = 0; col < matrixSize; col++) {
		
		for (int i = localCol; i < matrixSize; i += localSize) {
			bufB[i] = matrixB[i * matrixSize + col];
		}
	
		barrier(CLK_LOCAL_MEM_FENCE);
		
		sum = 0.0f;
		
		for (int i = 0; i < matrixSize; i++) {
			sum += bufA[i] * bufB[i];
		}
		
		matrixC[row * matrixSize + col] = sum;
		
		barrier(CLK_LOCAL_MEM_FENCE);
	}
}