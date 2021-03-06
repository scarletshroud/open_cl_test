#ifndef  _TEST_H_
#define  _TEST_H_

#include <vector>

class Test {
public:
	Test();
	Test(std::vector<double>& matrixA, std::vector<double>& matrixB, int matrixSize);
	~Test(); 

	std::vector<double>& matrixA();
	std::vector<double>& matrixB(); 

	int matrixSize(); 

private:
	std::vector<double> m_matrixA; 
	std::vector<double> m_matrixB;
	
	int m_matrixSize; 
};

#endif // ! TEST_H_

