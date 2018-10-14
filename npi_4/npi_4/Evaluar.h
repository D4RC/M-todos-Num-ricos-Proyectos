#pragma once
#include "Convertir.h"

class Eval
{
public:
	Eval(Conver x);
	~Eval();
	
	vector<string> npi;
	vector<double> pila;

	double a;
	double b;
	size_t tam;
	size_t soporte;

	double Evaluacion();

	void push(int signo);
	void push_r(double x);
	void push_s(double x);
	
	void pop();
	double top();

	int itr;
};

