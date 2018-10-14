#include "stdafx.h"
#include "Mtd_Matriz.h"


Mtd_Matriz::Mtd_Matriz()
{
	cout << "Filas | Columnas" << endl;
	cin >> filas >> columnas;

	matriz = new double *[filas];
	for (int i = 0; i<filas; i++)
	{
		matriz[i] = new double[columnas];

		for (int j = 0; j<columnas; j++)
		{
			cout << "Elemento [" << i << "][" << j << "]:\t";
			cin >> matriz[i][j];
		}
	}
}

Mtd_Matriz::Mtd_Matriz(double **Mat, int Fil, int Col)
{
	matriz = Mat;
	filas = Fil;
	columnas = Col;
}


Mtd_Matriz::~Mtd_Matriz()
{
	for (int i = 0; i < filas; i++)
		delete[] matriz[i];
	delete[] matriz;

	if(soluciones)
	delete[] soluciones;
}


bool Mtd_Matriz::verificar_cuadrada()
{
	if (filas == columnas - 1)
		return true;
	else
		return false;
}


void Mtd_Matriz::imprimir()
{
	cout << endl;
	for (int i = 0; i<filas; i++)
	{
		for (int j = 0; j<columnas; j++)
			cout << matriz[i][j] << "\t";
		cout << endl;
	}
}


bool Mtd_Matriz::verificar_diagonal()
{
	for (int i = 0; i<filas; i++)
		if (matriz[i][i] == 0)
			return false;

	return true;
}




//Metodo de Gauss Jordan
void Mtd_Matriz::Gauss_Jordan()
{
	if (verificar_cuadrada() == false)
	{
		cout << "El metodo de Gauss Jordan no puede aplicarse, la matriz no es cuadrada" << endl;
		return;
	}

	else
		for (int i = 0; i<filas; i++)
		{
			//Normalizar
			double divisor = matriz[i][i];
			for (int j = 0; j<columnas; j++)
				matriz[i][j] /= divisor;

			//Por cada fila distinta de i
			for (int k = 0; k<filas; k++)
				if (k != i)
				{
					//Empezando en la columna equivalente a i
					int j = i;
					//Encontrando el multiplicador para anular la columna respectiva
					double multiplicador = -matriz[k][j];
					for (; j < columnas; j++)
						matriz[k][j] += multiplicador * matriz[i][j];
				}
		}
}

//Metodo de Gauss Seidel
void Mtd_Matriz::Gauss_Seidel()
{
	if (verificar_cuadrada() == false)
	{
		cout << "El metodo de Gauss Seidel no puede aplicarse, la matriz no es cuadrada" << endl;
		return;
	}
	if (verificar_diagonal() == false)
	{
		cout << "El metodo de Gauss Seidel no puede aplicarse, se encontro un cero en la diagonal" << endl;
		return;
		//Nota: Agregar opcion de intercambio
	}


	//*st = soluciones triviales
	double *st = new double[filas];

	for (int i = 0; i<filas; i++)
		st[i] = matriz[i][columnas - 1];

	for (int i = 0; i<filas; i++)
	{
		for (int j = 0; j<columnas - 1; j++)
			st[i] -= matriz[i][j];

		st[i] /= matriz[i][i];
	}

}

double *Mtd_Matriz::retornar_soluciones()
{
	soluciones = new double[filas];
	for (int i = 0; i < filas; i++)
		soluciones[i] = matriz[i][columnas-1];
	return soluciones;
}