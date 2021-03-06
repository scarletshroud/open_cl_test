#include "test.h"

Test::Test() {
	m_matrixA = std::vector<double>(0);
	m_matrixB = std::vector<double>(0);
	m_matrixSize = 0;
}

Test::Test(std::vector<double>& matrixA, std::vector<double>& matrixB, int matrixSize) {
	m_matrixA = matrixA; 
	m_matrixB = matrixB;
	m_matrixSize = matrixSize;
}

Test::~Test() {

}

std::vector<double>& Test::matrixA() {
	return m_matrixA; 
}

std::vector<double>& Test::matrixB() {
	return m_matrixB; 
}

int Test::matrixSize() {
	return m_matrixSize;
}