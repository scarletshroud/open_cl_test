__kernel void transpose(
	__global double* input,
	__global double* output,
	int m,
	int n
)
{
	int col = get_global_id(0);
	int row = get_global_id(1);

	double k = input[row * m + col];

	if (col % 255 == 0 && row % 255 == 0)
		output[row * m + col] = k;
}