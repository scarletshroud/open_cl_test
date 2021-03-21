#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <string>

#include "host.h"
#include "test.h"
#include "one_core_cpu_test.h"
#include "answer.h"
#include "matrix_checker.h"
#include "tests_generator.h"

typedef std::vector<float> matrix;

double findDeviation(size_t n, double average, std::vector<double>& selection) {
    double sum = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum += (selection[i] - average) * (selection[i] - average);
    }

    return sqrt(sum / n);
}

int main() {
    size_t testsAmount = 1;
    size_t cycles = 1;
    size_t stepSize = 128;
    size_t initialValue = 0;

    CpuTest cpuTest;

    std::vector<Test> tests = generateTestsFromFile("./tests/", testsAmount);

    Host host;
    if (host.init() != 0) {
        std::cout << "Host initialization failed";
    }

    const char* transposeKernelPath = "./Kernels/TransposingKernel.cl";
    const char* mulKernelPath = "./Kernels/TiledKernel.cl";
    double prevExecutionTime = 1;

    std::map<size_t, Answer>  answers;

    for (size_t i = 0; i < testsAmount; ++i) {
        Test test = tests[i];

        matrix matrixA = test.matrixA();
        matrix matrixB = test.matrixB();

        int m = test.m();
        int n = test.n();
        int k = test.k();

        Answer answer(false, 0, m, k, std::vector<float>(0));
        std::vector<double> executionTimeSelection;

        double executionTimeSum = 0;
        double scaleSum = 0;

        for (size_t cycle = 1; cycle <= cycles; ++cycle) {

            if (host.multiplyMatrices(mulKernelPath, m, 32, matrixA, matrixB, m, n, k, answer) == -1) {
                return -1;
            }

            if (!checkMatrix(answer.data(), test.matrixC())) {
                answer.setIncorrect();
                break;
            }

            executionTimeSelection.push_back(answer.executionTime());
            executionTimeSum += answer.executionTime();
        }

        double executionTime = executionTimeSum / cycles;
        answer.setExecutionTime(executionTime);

        if (answer.isCorrect()) {
            answer.setFault(findDeviation(cycles, executionTime, executionTimeSelection));
            answer.setScale(executionTime / prevExecutionTime);
        }

        answers.insert(std::make_pair(i + 1, answer));

        prevExecutionTime = answer.executionTime();
    }

    for (const auto& ans : answers) {
        Answer answer = ans.second;

        std::cout << "Test " << ans.first << " | ";

        answer.isCorrect() == true ?
            std::cout << "Status: <OK>  | ":
            std::cout << "Status: <ERR> | ";

        std::cout << "Matrix Size: " << answer.m() << " x " << answer.k() << " | ";
        std::cout << "Execution time: " << answer.executionTime() << " ms | ";
        std::cout << "Standart Deviation: +-" << answer.deviation() << " ms | ";
        std::cout << "Scale: " << answer.scale() << " |" << std::endl;

    }

    return 0;
}
