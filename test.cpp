#include "test.h"

Test::Test() {
	m_matrixA = std::vector<float>(0);
	m_matrixB = std::vector<float>(0);
	m_matrixC = std::vector<float>(0);
	m_m = 0;
	m_n = 0;
	m_k = 0; 
}

Test::Test(std::vector<float>& matrixA, std::vector<float>& matrixB, std::vector<float>& matrixC, int m, int n, int k) {
	m_matrixA = matrixA; 
	m_matrixB = matrixB;
	m_matrixC = matrixC;
	m_m = m;
	m_n = n;
	m_k = k;
}

Test::~Test() {

}

std::vector<float>& Test::matrixA() {
	return m_matrixA; 
}

std::vector<float>& Test::matrixB() {
	return m_matrixB; 
}

std::vector<float>& Test::matrixC() {
	return m_matrixC;
}

int Test::m() {
	return m_m;
}

int Test::n() {
	return m_n;
}

int Test::k() {
	return m_k;
}