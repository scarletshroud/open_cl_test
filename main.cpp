#include <iostream>
#include <fstream>
#include <ctime>

#include "matrix_generator.h" 
#include "host.h"
#include "test.h"
#include "one_core_cpu_test.h"
 
typedef std::vector<double> matrix;

std::vector<Test> generateTestData(size_t amount, size_t step) {
    const size_t maxMatrixSize = 2500; 
    const size_t maxAmount = 10; 

    if (amount * step < maxMatrixSize && amount <= maxAmount) {
        std::vector<Test> tests(0);
        
        for (size_t i = 1; i <= 10; ++i) {
            matrix matrixA = generateMatrix(step * i);
            matrix matrixB = generateMatrix(step * i);

            Test test(matrixA, matrixB, step * i); 

            tests.push_back(test);
        }

        return tests;
    } 
    else {
        std::cout << "The limit of the matrix size exceeded." << std::endl;
    }
}

int main() {
    size_t testsAmount = 10; 
    size_t stepSize = 200; 

    std::vector<Test> tests = generateTestData(testsAmount, stepSize);
   
    Host host;
    if (host.init() != 0) {
        std::cout << "Host initialization failed"; 
    }


    const char* path = "./Kernels/NaiveKernel.cl";
    for (size_t i = 0; i < testsAmount; ++i) {
        Test test = tests[i];

        matrix matrixA = test.matrixA();
        matrix matrixB = test.matrixB();
        int matrixSize = test.matrixSize();

        host.testKernel(path, matrixSize, 4, matrixA, matrixB, matrixSize);
    }

    return 0;
}
