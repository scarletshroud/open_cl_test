#include "matrix_checker.h"
#include <iostream>

bool checkMatrix(std::vector<float>& result, std::vector<float>& example) {

	if (result.size() != example.size()) {
		return false;
	}

	size_t size = example.size();

	for (size_t i = 0; i < size; ++i) {
		if (abs(result[i] - example[i]) > 0.00000001f)
			return false;
	}

	return true;
}