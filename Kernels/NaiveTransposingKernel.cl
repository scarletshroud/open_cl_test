__kernel void transpose(
	__global const float* input,
	__global float* output,
	int rows,
	int cols
)
{
	int col = get_global_id(0);
	int row = get_global_id(1);

	output[col * rows + row] = input[row * cols + col];
}