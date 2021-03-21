#define TILE_SIZE 32
#define WPT 8
#define RTS 4

__kernel void MultiplyKernel(
	__global const float* matrixA,
	__global const float* matrixB,
	__global float* matrixC,
	int matrixSize
)
{
	const int row = get_local_id(0);
	const int col = get_local_id(1);

	const int globalRow = TILE_SIZE * get_group_id(0) + row;
	const int globalCol = TILE_SIZE * get_group_id(1) + col;

	__local float tileA[TILE_SIZE][TILE_SIZE];
	__local float tileB[TILE_SIZE][TILE_SIZE];

	float acc[WPT];
	for (unsigned int i = 0; i < WPT; i++) {
		acc[i] = 0.0f;
	}

	const int tilesAmount = matrixSize / TILE_SIZE;

	for (unsigned int tile = 0; tile < tilesAmount; tile++) {

		for (unsigned int k = 0; k < WPT; k++) {
			const int tileRow = TILE_SIZE * tile + row;
			const int tileCol = TILE_SIZE * tile + col;

			tileA[col + k * RTS][row] = matrixA[(tileCol + k * RTS) * matrixSize + globalRow];
			tileB[col + k * RTS][row] = matrixB[(globalCol + k * RTS) * matrixSize + tileRow];
		}

		barrier(CLK_LOCAL_MEM_FENCE);

		for (unsigned int i = 0; i < TILE_SIZE; i++) {
			for (unsigned int j = 0; j < WPT; j++) {
				acc[j] += tileA[i][row] * tileB[col + j * RTS][i];
			}
		}

		barrier(CLK_LOCAL_MEM_FENCE);
	}

	for (unsigned int i = 0; i < WPT; i++) {
		matrixC[(globalCol + i * RTS) * matrixSize + globalRow] = acc[i];
	}
}