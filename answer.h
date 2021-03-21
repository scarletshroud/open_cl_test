#ifndef _ANSWER_H_
#define _ANSWER_H_

#include <vector>

class Answer
{
public:
	Answer(bool isCorrect, double time, int m, int k, std::vector<float> data);
	~Answer();

	bool isCorrect();
	double executionTime();

	int m();
	int k();

	double deviation();
	double scale();

	std::vector<float>& data();

	void setCorrect();
	void setIncorrect();

	void setFault(double fault);
	void setScale(double scale);

	void setExecutionTime(double time);
	void setData(std::vector<float> data);

private:
	bool m_correct;
	double m_executionTime;

	int m_m;
	int m_k;

	double m_scale; 
	double m_deviation;

	std::vector<float> m_data;
};

#endif