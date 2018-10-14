#include "stdafx.h"
#include "Matriz_dinamica.h"
#include "math.h"

CMatriz_dinamica::CMatriz_dinamica(int x, int y)
{
	filas = x;
	columnas = y;
	for (i = 0; i < filas; i++)
	{
		matriz[i] = new double[columnas];
		for (j = 0; j < columnas; j++)
		{
			cout << "Ingresar elemento x[" << i << "][" << j << "]:\t";
			cin >> matriz[i][j];
		}
	}
}


CMatriz_dinamica::~CMatriz_dinamica()
{
	for (i = 0; i < filas; i++)
		delete[] matriz[i];
	delete[] matriz;

	cin.get();
	cin.get();
}


bool CMatriz_dinamica::verificar_simetria()
{
	if (filas == columnas - 1)
	{
		orden = filas;
		return true;
	}
	else
		return false;
}


void CMatriz_dinamica::intercambiar(int a, int b)
{
	cout << "Intercambiando fila" << a << " por fila " << b << endl;
	double *auxiliar = new double[columnas];
	for (i = 0; i < columnas; i++)
	{
		auxiliar[i] = matriz[a - 1][i];
		matriz[a - 1][i] = matriz[b - 1][i];
		matriz[b - 1][i] = auxiliar[i];
	}
	delete[] auxiliar;
}


double CMatriz_dinamica::determinante(int x)
{
	int orden_temporal = x;
	if (orden_temporal==2)
	{
		return 
	}
}


double CMatriz_dinamica::determinante(double **mat, int x)
{
	Det = 0;

	if (x == 1)
		return mat[0][0];

	else if (x == 2)
		//Retorno en caso orden de matriz (x) == 2
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];




		
}


