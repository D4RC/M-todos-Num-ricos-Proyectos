// mtd_10.cpp: define el punto de entrada de la aplicación de consola.
// Metodo de cramer

#include "stdafx.h"
#include <iostream>
#include "math.h"

using namespace std;

void main()
{
	int dimensiones;
	double **matriz = new double *[dimensiones];

	cout << "Ingreso de matriz simetrica:\nFilas:\t";
	cin >> dimensiones;

	almacenamiento(dimensiones, matriz);

}

void almacenamiento(int dim, double **matriz)
{
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim + 1; j++)
		{
			cout << "Ingresar elemento x[" << i << "][" << j << "]:\t";
			cin >> matriz[i][j];
		}
}

