#pragma once
#include <iostream>
using namespace std;

class CEquation
{
public:
	CEquation(void);
	~CEquation(void);

	int grade;
	int counter;
	double temporal[10];
	double data[10];

	void storage();
	void storage(double *polinomio, int grado);
	void print();
	void temporal_storage();
};

