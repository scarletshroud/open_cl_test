#include "answer.h"

Answer::Answer(bool isCorrect, double time, int m, int k, std::vector<float> data) {
	m_correct = isCorrect;
	m_executionTime = time;

	m_m = m;
	m_k = k;

	m_deviation = 0;
	m_scale = 0;

	m_data = data;
}

Answer::~Answer() {

}
bool Answer::isCorrect() {
	return m_correct;
}

double Answer::executionTime() {
	return m_executionTime;
}

int Answer::m() {
	return m_m;
}

int Answer::k() {
	return m_k;
}

double Answer::deviation() {
	return m_deviation;
}

double Answer::scale() {
	return m_scale;
}

std::vector<float>& Answer::data() {
	return m_data;
}

void Answer::setCorrect() {
	m_correct = true;
}

void Answer::setIncorrect() {
	m_correct = false;
}

void Answer::setFault(double fault) {
	m_deviation = fault;
}

void Answer::setScale(double scale) {
	m_scale = scale;
}

void Answer::setExecutionTime(double time) {
	m_executionTime = time;
}

void Answer::setData(std::vector<float> data) {
	m_data = data;
}
