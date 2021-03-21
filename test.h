#ifndef  _TEST_H_
#define  _TEST_H_

#include <vector>

class Test {
public:
	Test();
	Test(std::vector<float>& matrixA, std::vector<float>& matrixB, std::vector<float>& matrixC, int m, int n, int k);
	~Test(); 

	std::vector<float>& matrixA();
	std::vector<float>& matrixB();
	std::vector<float>& matrixC();

	int m(); 
	int n();
	int k();

private:
	std::vector<float> m_matrixA; 
	std::vector<float> m_matrixB;
	std::vector<float> m_matrixC;
	
	int m_m;
	int m_n;
	int m_k;
};

#endif // ! TEST_H_

