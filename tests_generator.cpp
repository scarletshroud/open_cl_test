#include "tests_generator.h"
#include "matrix_generator.h" 

std::vector<Test> generateTests(size_t amount, size_t initialValue, size_t step) {
    const size_t maxMatrixSize = 4000;
    const size_t maxAmount = 30;

    if (initialValue + amount * step < maxMatrixSize && amount <= maxAmount) {
        std::vector<Test> tests(0);

        for (size_t i = 1; i <= amount; ++i) {

            std::vector<float> matrixA = generateMatrix(initialValue + step * i);
            std::vector<float> matrixB = generateMatrix(initialValue + step * i);
            std::vector<float> matrixC(0);

            Test test(matrixA, matrixB, matrixC, initialValue + step * i, initialValue + step * i, initialValue + step * i);

            tests.push_back(test);
        }

        return tests;
    }
    else {
        std::cout << "The limit of the matrix size exceeded." << std::endl;
    }
}

std::vector<Test> generateTestsFromFile(const std::string path, size_t amount) {
    
    std::vector<Test> tests(0);

    for (size_t i = 1; i <= amount; ++i) {
       
        std::string filename = path + "test" + std::to_string(i) + ".txt";

        Test test = readTestFromFile(filename.c_str());

        tests.push_back(test);
    }

    return tests;
}