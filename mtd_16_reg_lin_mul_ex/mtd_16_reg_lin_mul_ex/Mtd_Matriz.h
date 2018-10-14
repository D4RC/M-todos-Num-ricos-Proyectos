#pragma once
#include <iostream>
using namespace std;

class Mtd_Matriz
{
public:
	Mtd_Matriz();
	Mtd_Matriz(double **Mat, int Fil, int Col);
	~Mtd_Matriz();

	int filas, columnas;
	double **matriz;
	double *soluciones=NULL;
	void Gauss_Jordan();
	void Gauss_Seidel();
	void imprimir();
	bool verificar_cuadrada();
	bool verificar_diagonal();
	double *retornar_soluciones();
};

