__kernel void transpose(
	__global const float* input,
	__global float* output,
	int m,
	int n
) {
	int row = get_global_id(0);

	for (int i = 0; i < n; ++i) {
		output[row * n + i] = input[row * n + i];
	}
}