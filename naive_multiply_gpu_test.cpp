#include <iostream>
#include <fstream>
#include <chrono>

#include "naive_multiply_gpu_test.h"

NaiveGpuTest::NaiveGpuTest() {
    m_matrixA = matrix(0);
    m_matrixB = matrix(0);
    m_matrixC = matrix(0);

    m_matrix_size = 0;
}

NaiveGpuTest::~NaiveGpuTest() {

}

int NaiveGpuTest::init(matrix& matrixA, matrix& matrixB, matrix& matrixC, int matrix_size) {
    std::vector <cl::Platform> platforms;
    cl::Platform::get(&platforms);

    if (platforms.size() == 0) {
        std::cout << "Naive GPU Test: No platforms found. Check CUDA installation" << std::endl;
        return -1;
    }

    std::vector<cl::Device> devices;
    platforms[0].getDevices(CL_DEVICE_TYPE_GPU, &devices);

    if (devices.size() == 0) {
        std::cout << "Naive GPU Test: Devices found: 0" << std::endl;
        return -1;
    }

    if (matrixA.size() == 0) {
        std::cout << "Naive GPU Test: Matrix A is empty";
        return -1;
    }

    if (matrixB.size() == 0) {
        std::cout << "Naive GPU Test: Matrix B is empty";
        return -1;
    }

    if (matrixC.size() == 0) {
        std::cout << "Naive GPU Test: Matrix C is empty";
        return -1;
    }

    if (matrixA.size() != matrixB.size()) {
        std::cout << "Naive GPU Test: The number of rows of matrix A is not equal to the number of columns of matrix B";
        return -1;
    }

    m_device = devices[0];

    m_matrixA = matrixA; 
    m_matrixB = matrixB;
    m_matrixC = matrixC; 

    m_matrix_size = matrix_size; 

    return 0; 
}

int NaiveGpuTest::test() {
    std::vector<cl::Device> contextDevices;
    contextDevices.push_back(m_device);
    cl::Context context(contextDevices);

    cl::CommandQueue queue(context, m_device);

    cl::Buffer inputMatrixA = cl::Buffer(
        context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR,
        m_matrix_size * m_matrix_size * sizeof(double), (void*) m_matrixA.data()
    );

    cl::Buffer inputMatrixB = cl::Buffer(
        context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR,
        m_matrix_size * m_matrix_size * sizeof(double), (void*) m_matrixB.data()
    );

    cl::Buffer outputMatrixC = cl::Buffer(
        context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        m_matrix_size * m_matrix_size * sizeof(double), (void*) m_matrixC.data()
    );

    std::ifstream sourceFile("C:/Users/nooba/source/repos/test_cl/test_cl/MultiplyKernel.cl");
    std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));

    cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
    cl::Program program = cl::Program(context, source);

    int clPrg = program.build(contextDevices);
    if (clPrg != CL_SUCCESS) {
        std::cout << "An error occurred while building the kernel program. Please, check the build log." << std::endl;
        std::cout << "Error Code:" << clPrg << std::endl;

        std::ofstream out;
        out.open("buildClLog.txt");

        if (out.is_open()) {
            out << "Program build info: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_device) << std::endl;
        }

        out.close();

        return -1;
    }

    cl::Kernel kernel(program, "MultiplyKernel");

    int iArg = 0;
    kernel.setArg(iArg++, inputMatrixA);
    kernel.setArg(iArg++, inputMatrixB);
    kernel.setArg(iArg++, outputMatrixC);
    kernel.setArg(iArg++, m_matrix_size);

    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "Naive matrix multiplication on GPU started..." << std::endl;
    int clEnq = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(m_matrix_size, m_matrix_size), cl::NDRange(8, 8));
    if (clEnq != CL_SUCCESS) {
        std::cout << "An error occurred while adding a command to the queue to execute a kernel on a device." << std::endl;
        std::cout << "Error Code: " << clEnq << std::endl; 
        return -1;
    }

    queue.finish();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    queue.enqueueReadBuffer(outputMatrixC, CL_TRUE, 0,
        m_matrix_size * m_matrix_size * sizeof(double), (void*) m_matrixC.data());

    std::cout << std::endl << "-----------Matrix-Multiplication-Is-Successful-----------" << std::endl;
    std::cout << "Computing Device: " << m_device.getInfo<CL_DEVICE_NAME>() <<  std::endl;
    std::cout << "Matrix Size: " << m_matrix_size << std::endl;
    std::cout << "Compution time: " << duration << "ms" << std::endl;
    std::cout << "---------------------------------------------------------" << "\n\n";
    return 0;
}