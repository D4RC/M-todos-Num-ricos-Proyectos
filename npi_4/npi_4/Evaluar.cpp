#include "stdafx.h"
#include "Evaluar.h"
#include "math.h"

#define PI 3.14159265

Eval::Eval(Conver x)
{
	npi = x.dir();
	tam = npi.size();
}


Eval::~Eval()
{
}


double Eval::Evaluacion()
{
	for (itr = 0; itr < tam; itr++)
	{
		soporte = 0;

		if (pila.size()>=2)
		{
			a = pila[pila.size() - 2];
			b = pila[pila.size() - 1];
		}

		switch (npi[itr][0])
		{
		case '+':
			push_r(a + b);
			break;

		case '-':
			if (npi[itr].size() > 1)
			{
				soporte = 1;
				push(-1);
			}
			else
			{
				push_r(a - b);
			}
			break;


		case '*':
			push_r(a * b);
			break;

		case '/':
			push_r(a / b);
			break;

		case '^':
			push_r(pow(a, b));
			break;

		case 's':
			push_s(sin(top() * PI / 180.0));
			break;

		case 't':
			push_s(tan(top() * PI / 180.0));
			break;

		case 'c':
			push_s(cos(top() * PI / 180.0));
			break;

		case 'e':
			push_s(exp(top()));
			break;

		default:
			push(1);
			break;
		}
	}


	return pila.back();
}

void Eval::push(int signo)
{
	double numero;
	numero = stod(npi[itr], &soporte);
	numero *= signo;
	pila.push_back(numero);
}

void Eval::push_r(double x)
{
	pila.pop_back();
	pila.pop_back();
	pila.push_back(x);
}

void Eval::push_s(double x)
{
	pila.pop_back();
	pila.push_back(x);
}

double Eval::top()
{
	return pila.back();
}

void Eval::pop()
{
	pila.pop_back();
}




