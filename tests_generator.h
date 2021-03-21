#ifndef  _TESTS_GENERATOR_H_
#define _TESTS_GENERATOR_H_

#include <vector>
#include <string>

#include "test.h"
#include "test_reader.h"

std::vector<Test> generateTests(size_t amount, size_t initialValue, size_t step);
std::vector<Test> generateTestsFromFile(const std::string path, size_t amount);

#endif // ! _TESTS_GENERATOR_H_


