__kernel void transpose(
	__global const float* input, 
	__global float* output,
	int m,
	int n
) {
	int col = get_global_id(0);
	int row = get_global_id(1);

	output[row * m + col] = input[row * m + col];
}