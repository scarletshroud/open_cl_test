#include <iostream>
#include <fstream>
#include <chrono>

#include "host.h"

Host::Host() {
 
}

Host::~Host() {

}

int Host::init() {
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

    m_device = devices[0];

    return 0; 
}

int Host::checkParams(matrix& matrixA, matrix& matrixB, int matrixSize) {
    if (matrixA.size() == 0) {
        std::cout << "Naive GPU Test: Matrix A is empty";
        return -1;
    }

    if (matrixB.size() == 0) {
        std::cout << "Naive GPU Test: Matrix B is empty";
        return -1;
    }

    if (matrixA.size() != matrixB.size()) {
        std::cout << "Naive GPU Test: The number of rows of matrix A is not equal to the number of columns of matrix B";
        return -1;
    }

    return 0; 
}

int Host::testKernel(const char* kernelPath, int workItems, int workGroups, matrix& matrixA, matrix& matrixB, int matrixSize) {
   
    if (checkParams(matrixA, matrixB, matrixSize) != 0) {
        return -1; 
    }

    std::vector<cl::Device> contextDevices;
    contextDevices.push_back(m_device);
    cl::Context context(contextDevices);

    cl::CommandQueue queue(context, m_device, CL_QUEUE_PROFILING_ENABLE);

    cl::Buffer inputMatrixA = cl::Buffer(
        context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR,
        matrixSize * matrixSize * sizeof(double), (void*) matrixA.data()
    );

    cl::Buffer inputMatrixB = cl::Buffer(
        context, CL_MEM_READ_ONLY  | CL_MEM_COPY_HOST_PTR,
        matrixSize * matrixSize * sizeof(double), (void*) matrixB.data()
    );

    matrix matrixC(matrixSize * matrixSize);
    cl::Buffer outputMatrixC = cl::Buffer(
        context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        matrixSize * matrixSize * sizeof(double), (void*) matrixC.data()
    );

    std::ifstream sourceFile(kernelPath);
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
    kernel.setArg(iArg++, matrixSize);

    cl::Event event;

    int clEnq = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(workItems, workItems), cl::NDRange(workGroups, workGroups), NULL, &event);
    if (clEnq != CL_SUCCESS) {
        std::cout << "An error occurred while adding a command to the queue to execute a kernel on a device." << std::endl;
        std::cout << "Error Code: " << clEnq << std::endl; 
        return -1;
    }

    queue.finish();

    cl_ulong startTime; 
    cl_ulong endTime;

    event.getProfilingInfo(CL_PROFILING_COMMAND_START, &startTime); 
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &endTime);

    double milliseconds = (endTime - startTime) / 1000000.0; 

    queue.enqueueReadBuffer(
        outputMatrixC, CL_TRUE, 0,
        matrixSize * matrixSize * sizeof(double), (void*) matrixC.data()
    );

    std::cout << "<OK> | Matrix Size: " << matrixSize << " x " << matrixSize << " | " << "Compution time: " << milliseconds << " ms |\n" << std::endl;

    return 0;
}