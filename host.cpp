#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

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

int Host::validateParams(matrix& matrixA, matrix& matrixB) {
    if (matrixA.size() == 0) {
        std::cout << "Naive GPU Test: Matrix A is empty";
        return -1;
    }

    if (matrixB.size() == 0) {
        std::cout << "Naive GPU Test: Matrix B is empty";
        return -1;
    }

    return 0;
}

cl::Program Host::buildProgramOnDevice(const char* kernelPath, cl::Context& context, std::vector<cl::Device>& contextDevices) {
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
    }

    return program;
}


int Host::multiplyMatrices(const char* kernelPath, int workItems, int workGroups, matrix& matrixA, matrix& matrixB, int m, int n, int k, Answer& answer) {

    if (validateParams(matrixA, matrixB) != 0) {
        return -1;
    }

    std::vector<cl::Device> contextDevices;
    contextDevices.push_back(m_device);
    cl::Context context(contextDevices);

    cl::CommandQueue queue(context, m_device, CL_QUEUE_PROFILING_ENABLE);

    cl::Buffer inputMatrixA = cl::Buffer(
        context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        m * n * sizeof(float), (void*)matrixA.data()
    );

    cl::Buffer inputMatrixB = cl::Buffer(
        context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        n * k * sizeof(float), (void*)matrixB.data()
    );

    matrix matrixC(m * k);
    cl::Buffer outputMatrixC = cl::Buffer(
        context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        m * k * sizeof(float), (void*)matrixC.data()
    );

    cl::Program mulKernelProgram = buildProgramOnDevice(kernelPath, context, contextDevices);

    cl::Kernel kernel(mulKernelProgram, "MultiplyKernel");

    int iArg = 0;
    kernel.setArg(iArg++, inputMatrixA);
    kernel.setArg(iArg++, inputMatrixB);
    kernel.setArg(iArg++, outputMatrixC);
    kernel.setArg(iArg++, m);
    kernel.setArg(iArg++, n);
    kernel.setArg(iArg++, k);

    cl::Event event;

    size_t global_size_m; 
    m % 32 != 0 ? global_size_m = 32 * (m / 32 + 1) : global_size_m = m; 

    size_t global_size_k;
    k % 32 != 0 ? global_size_k = 32 * (k / 32 + 1) : global_size_k = k;

    int clEnq = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(global_size_m, global_size_k), cl::NDRange(32, 32), NULL, &event);
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
        m * k * sizeof(float), (void*)matrixC.data()
    );

    answer.setCorrect();
    answer.setExecutionTime(milliseconds);
    answer.setData(matrixC);

    return 0;
}

int Host::transposeMatrix(const char* kernelPath, matrix& matr, matrix& transposedMatrix, int m, int n) {

    std::vector<cl::Device> contextDevices;
    contextDevices.push_back(m_device);
    cl::Context context(contextDevices);

    cl::CommandQueue queue(context, m_device, CL_QUEUE_PROFILING_ENABLE);

    cl::Program program = buildProgramOnDevice("./Kernels/TransposingKernel.cl", context, contextDevices);

    matrix tmatr(m * n);

    cl::Buffer inputBuf = cl::Buffer(
        context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        m * n * sizeof(float), (void*)matr.data()
    );

    cl::Buffer outputBuf = cl::Buffer(
        context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
        m * n * sizeof(float), (void*)tmatr.data()
    );

    cl::Kernel kernel(program, "transpose");

    int iArg = 0;
    kernel.setArg(iArg++, inputBuf);
    kernel.setArg(iArg++, outputBuf);
    kernel.setArg(iArg++, m);
    kernel.setArg(iArg++, n);

    cl::Event event;

    int clEnq = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(m, n), cl::NDRange(32, 32), NULL, &event);
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
        outputBuf, CL_TRUE, 0,
        m * n * sizeof(float), (void*)tmatr.data()
    );

  /*for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++)
            std::cout << transposedMatrix[i * cols + j] << " ";
        std::cout << std::endl;
    } */

    transposedMatrix = tmatr;

    return 0; 
}