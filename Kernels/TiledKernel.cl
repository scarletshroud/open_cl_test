#define TILE_SIZE 32
__kernel void MultiplyKernel(
	__global const double* matrixA,
	__global const double* matrixB,
	__global double* matrixC, 
	int m,
	int n,
	int k
) 
{
	const int tileRow = get_local_id(0);
	const int tileCol = get_local_id(1); 

	const int globalRow = get_global_id(0);
	const int globalCol = get_global_id(1); 

	__local double tileA[TILE_SIZE][TILE_SIZE]; 
	__local double tileB[TILE_SIZE][TILE_SIZE];

	double sum = 0.0f;

	const int additionalTile = (n % TILE_SIZE != 0);
	const int tilesAmount = n / TILE_SIZE + additionalTile;

	for (unsigned int tile = 0; tile < tilesAmount; tile++) {

		const int row = TILE_SIZE * tile + tileRow;
		const int col = TILE_SIZE * tile + tileCol; 

		if (globalRow < m && col < n)
			tileA[tileRow][tileCol] = matrixA[globalRow * n + col];
		else
			tileA[tileRow][tileCol] = 0; 

		if (globalCol < k && row < n)
			tileB[tileRow][tileCol] = matrixB[row * k + globalCol];
		else
			tileB[tileRow][tileCol] = 0;

		barrier(CLK_LOCAL_MEM_FENCE);

		for (unsigned int i = 0; i < TILE_SIZE; i++) {
			sum += tileA[tileRow][i] * tileB[i][tileCol];
		}

		barrier(CLK_LOCAL_MEM_FENCE);
	}

	if (globalRow < m && globalCol < k) {
		matrixC[globalRow * k + globalCol] = sum;
	}
}