#define MAX_SIZE 3200
__kernel void MultiplyKernel(
	__global const float* matrixA, 
	__global const float* matrixB, 
	__global float* matrixC, 
	int matrixSize
) {
	int row = get_global_id(0);
	
	__local bufA[MAX_SIZE];
	
	float sum;
	
	for (int col = 0; col < matrixSize; col++) {
		sum = 0.0;
			
		for (int i = 0; i < matrixSize; i++) {
			sum += matrixA[row * matrixSize + i] * matrixB[col * matrixSize + i];
		}
		
		barrier(CLK_LOCAL_MEM_FENCE);
		
		matrixC[row * matrixSize + col] = sum;
	}
}