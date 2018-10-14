#include "stdafx.h"
#include "Equation.h"


CEquation::CEquation(void)
{
	for (int i = 0; i <= grade; i++)
	{
		data[i] = 0;
		temporal[i] = 0;
	}
}


CEquation::~CEquation(void)
{
}



void CEquation::storage()
{
	cout << "Storage" << endl;
	cout << "Enter equation grade:\t";
	cin >> grade;

	for (int i = grade; i >= 0; i--)
	{
		cout << "Term grade [" << i << "]:\t";
		cin >> data[i];
	}
}

void CEquation::storage(double *polinomio, int grado)
{
	for (int i = grado; i >= 0; i--)
		data[i] = polinomio[i];
	grade=grado;
}

void CEquation::print()
{
	for (int i = grade; i >= 0; i--)
		cout << "R[" << i << "]:\t" << data[i] << endl;
}

void CEquation::temporal_storage()
{
	for (int i = grade; i >= 0; i--)
		temporal[i] = data[i];
	counter = grade;
}
