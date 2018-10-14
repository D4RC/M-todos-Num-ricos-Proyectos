#pragma once
#include <iostream>
using namespace std;

class CMatriz_dinamica
{
public:
	CMatriz_dinamica(int x, int y);
	~CMatriz_dinamica();

	int filas;
	int columnas;
	int orden;
	int i;
	int j;
	int orden_temporal;			 //Orden temporal
	double Det;

	double **matriz=new double *[filas];
	bool verificar_simetria();
	void intercambiar(int a, int b);
	double determinante(int x);
	double determinante(double **mat, int x);
	

};



