// mtd_17_interpol_Newton.cpp
// Interpolación de Newton
// 1273096

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct puntos {
	double *x;	//Datos x
	double *y;	//Datos f(x)
	int num;	//Numero de datos
};

char f = 159;
void ingresar_puntos(puntos &P);
void lectura_puntos(puntos &P);
double diferencia(puntos P, int a, int b);

int main()
{
	cout << "Interpolacion con diferencias divididas de Newton" << endl;

	puntos P;
	double *b;	//Coeficientes del polinomio de interpolación
	double x;	//
	double y;	//ƒ(x)	Valor que se desea aproximar con el polinomio obtenido
	double m;	//auxiliar
	bool sel;

	cout << "Insercion de puntos automatica?	[1]Si	[0]No:	";
	cin >> sel;

	(sel) ? lectura_puntos(P) : ingresar_puntos(P);
	cout << "\nSe obtendra un polinomio de interpolacion de grado " << P.num - 1 << endl << endl;

	//Proceso
	b = new double[P.num];
	b[0] = P.y[0];
	for (int i = 1; i < P.num; i++)
		b[i] = diferencia(P, i, 0);

	//Resultados de coeficientes
	cout << "Coeficientes b_0, b_1, ... ,b_n del polinomio resultantes" << endl;
	for (int i = 0; i < P.num; i++)
		cout << "b[" << i << "]:\t" << b[i] << endl;

	cout << "\nIngresar un valor intermedio de x para calcular una aproximacion" << endl;
	cout << "x:\t";
	cin >> x;

	y = b[0];
	m = 1;

	for (int i = 1; i < P.num; i++)
	{
		m *= x - P.x[i - 1];	//Se acumularan las multiplicaciones en m
		y += b[i] * m;
	}
	cout << f << "(" << x << ") = \t" << y;

	delete[] P.x, P.y;
	cin.get();
	cin.get();
}

void ingresar_puntos(puntos &P)
{
	cout << "Numero de puntos a ingresar:\t";
	cin >> P.num;

	P.x = new double[P.num];
	P.y = new double[P.num];

	cout << "Ingresar los pares de datos por cada punto:" << endl;
	for (int i = 0; i < P.num; i++)
	{
		cout << "x_" << i << ":\t";
		cin >> P.x[i];
		cout << f << "(x_" << i << "):\t";
		cin >> P.y[i];
	}
}

/*
Diferencia finita
@param P	struct de datos de los puntos
@param a	indice del dato como minuendo
@param b	indice del dato como sustraendo
*/
double diferencia(puntos P, int a, int b)
{
	//Caso base	diferencia 1

	if (a - b == 1)
		return (P.y[a] - P.y[b]) / (P.x[a] - P.x[b]);

	//Paso de recursividad diferencia >1

	else
		return (diferencia(P, a, b + 1) - diferencia(P, a - 1, b)) / (P.x[a] - P.x[b]);
}

//Lectura automatica de un fichero txt
void lectura_puntos(puntos &P)
{
	string archivo;
	string temporal;

	cout << "Ingresar archivo de origen de datos:\t";
	cin >> archivo;

	ifstream data;
	data.open(archivo, ios::in);

	if (data.fail())
	{
		cout << "Error, no se pudo abrir el archivo " << archivo << endl;
		system("pause");
		exit(1);
	}

	P.num = 0;
	while (!data.eof())
	{
		getline(data, temporal);
		P.num++;
	}

	P.x = new double[P.num];
	P.y = new double[P.num];

	data.clear();				//Limpieza de banderas
	data.seekg(0, ios::beg);	//Restaurar a posicion 0 en relacion a ios::beg (comienzo del stream) 

	cout << "Lectura:" << endl;
	cout << "x:\t" << f << "(x)" << endl;

	for (int i = 0; !data.eof(); i++)
	{
		getline(data, temporal, '\t');
		P.x[i] = stod(temporal);
		getline(data, temporal);
		P.y[i] = stod(temporal);
		cout << P.x[i] << "\t" << P.y[i] << endl;
	}
	data.close();
}