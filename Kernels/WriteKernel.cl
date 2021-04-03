__kernel void transpose(
	__global float* input,
	__global float* output,
	int m,
	int n
)
{
	int col = get_global_id(0);
	int row = get_global_id(1);

	float k = 1.0;

	output[row * m + col] = k;
}