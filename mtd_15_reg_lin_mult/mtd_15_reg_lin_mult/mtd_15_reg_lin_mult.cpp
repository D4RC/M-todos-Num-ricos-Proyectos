// mtd_15_reg_lin_mult.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
//	Se actualizo el visual studio jajajaja

//	REGRESIÓN LINEAL MÚLTIPLE
//	Daniel Alejandro Rodríguez Castro	
//	A01273096

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "math.h"
#include "Mtd_Matriz.h"
using namespace std;

struct variables {
	double *x = NULL, *y = NULL, *z = NULL;
	int tam = 0;
};

double *lectura(int &contador);
void lectura_multiple(variables &V);
void variable_dependiente(variables &V);

int main()
{
	cout << "Regresion Lineal Multiple:\t\tFuncion de dos variables z = " << char(159) << "(x,y)" << endl << endl;

	variables V;

	double sx = 0, sy = 0, sz = 0;
	double sx2 = 0;	//sx^2
	double sy2 = 0;	//sy^2
	double sxz = 0, syz = 0, sxy = 0;

	double **M = NULL;	//Es dinámica porque asi puedo usar la clase de mtd_Gauss


	double *A_i = NULL;		//Coeficientes de regresión 

	//Lectura de datos
	lectura_multiple(V);

	//Selección de la variable dependiente (Activar/Desactivar si es necesario)
	//Por default la tercer columna es z = f(x,y)
	variable_dependiente(V);

	//Sumatorias 
	for (int i = 0; i < V.tam; i++)
	{
		sx += V.x[i];
		sy += V.y[i];
		sz += V.z[i];
		sx2 += pow(V.x[i], 2);
		sy2 += pow(V.y[i], 2);
		sxz += V.x[i] * V.z[i];
		syz += V.y[i] * V.z[i];
		sxy += V.x[i] * V.y[i];
	}

	//Formacion de Matriz
	M = new double *[3];
	for (int i = 0; i < 3; i++)
		M[i] = new double[4];

	M[0][0] = V.tam;
	M[0][1] = sx;
	M[0][2] = sy;
	M[0][3] = sz;
	M[1][0] = sx;
	M[1][1] = sx2;
	M[1][2] = sxy;
	M[1][3] = sxz;
	M[2][0] = sy;
	M[2][1] = sxy;
	M[2][2] = sy2;
	M[2][3] = syz;

	//Gauss-Jordan
	Mtd_Matriz *sol = new Mtd_Matriz(M, 3, 4);
	sol->imprimir();
	sol->Gauss_Jordan();
	cout << "\nAplicando metodo de Gauss-Jordan" << endl;
	sol->imprimir();
	A_i = sol->retornar_soluciones();

	//Regresión múltiple
	variables R;
	cout << "\nResultado del ajuste lineal:	z = " << A_i[0] << " + " << A_i[1] << "x + " << A_i[2] << "y" << endl;
	cout << "Calculando valores de z" << endl << endl;

	//Dominio
	int x_max = V.x[0], x_min = V.x[0], y_max = V.y[0], y_min = V.y[0];
	for (int i = 0; i < V.tam; i++)
	{
		if (V.x[i] > x_max)
			x_max = V.x[i];
		if (V.x[i] < x_min)
			x_min = V.x[i];
		if (V.y[i] > y_max)
			y_max = V.y[i];
		if (V.y[i] < y_min)
			y_min = V.y[i];
	}

	int nx = x_max - x_min + 1;
	int ny = y_max - y_min + 1;
	R.tam = nx * ny;

	R.x = new double[R.tam];
	R.y = new double[R.tam];
	R.z = new double[R.tam];

	nx--;
	ny--;

	for (int i = 0, k = x_min; i <= nx; i++, k++)
		for (int j = 0; j <= ny; j++)
			R.x[i + j + ny * i] = k;

	for (int i = 0; i <= nx; i++)
		for (int j = 0, k = y_min; j <= ny; j++, k++)
			R.y[i + j + ny * i] = k;


	cout << "\nx\ty\tz" << endl;
	for (int i = 0; i < R.tam; i++)
	{
		R.z[i] = A_i[0] + A_i[1] * R.x[i] + A_i[2] * R.y[i];
		cout << R.x[i] << "\t" << R.y[i] << "\t" << R.z[i] << endl;
	}


	delete[] V.x, V.y, V.z, R.x, R.y, R.z;
	delete sol;
}

void lectura_multiple(variables &V)
{
	string archivo, temporal;

	cout << "Ingresar archivo de origen de datos:\t";
	cin >> archivo;

	ifstream data;
	data.open(archivo, ios::in);		//ios::in Bandera modo de entrada

	if (data.fail())
	{
		cout << "No se pudo abrir el archivo " << archivo << endl;
		cout << "Ingresar correctamente el nombre del archivo con su extension" << endl;
		cout << "Verificar que este en la carpeta del proyecto o anadir su ubicacion" << endl;
		system("pause");
		exit(1);
	}


	while (!data.eof())			//Determinando el tamaño de arreglos dinamicos
	{
		getline(data, temporal);
		V.tam++;
	}

	V.x = new double[V.tam];
	V.y = new double[V.tam];
	V.z = new double[V.tam];

	data.clear();				//Limpieza de banderas
	data.seekg(0, ios::beg);	//Restaurar a posicion 0 en relacion a ios::beg (comienzo del stream) 

	//Nota: verificar que el archivo de origen no termine en linea vacia, de lo contrario stod produce exepción
	//Asimismo que no haya una linea vacia entre datos

	char delimitador = '\t';			//Por defecto el delimitador lo estableci como el tabulador, cambiar si es necesario
	size_t encontrar;					//Se cambiara automaticamente a una , si el archivo es un csv
	encontrar = archivo.rfind(".csv");
	if (encontrar != string::npos)
		delimitador = ',';

	cout << "Lectura:" << endl;

	for (int i = 0; !data.eof(); i++)
	{

		getline(data, temporal, delimitador);
		V.x[i] = stod(temporal, NULL);

		getline(data, temporal, delimitador);
		V.y[i] = stod(temporal, NULL);

		getline(data, temporal);
		V.z[i] = stod(temporal, NULL);

		cout << V.x[i] << "\t" << V.y[i] << "\t" << V.z[i] << endl;
	}
	data.close();
}

double *lectura(int &contador)
{
	string archivo;
	string temporal;
	contador = 0;
	size_t auxiliar;

	cout << "Ingresar archivo de origen de datos:\t";
	cin >> archivo;

	ifstream data;
	data.open(archivo, ios::in);	//ios::in Bandera de operaciones de entrada

	if (data.fail())
	{
		cout << "Error, no se pudo abrir el archivo " << archivo << endl;
		system("pause");
		exit(1);
	}

	while (!data.eof())			//Bloque para determinar el tamaño del arreglo dinámico
	{							//!eof Mientras no haya terminado el archivo
		getline(data, temporal);
		contador++;
	}


	double *array = new double[contador];

	contador = 0;

	data.clear();				//Limpieza de banderas
	data.seekg(0, ios::beg);	//Restaurar a posicion 0 en relacion a ios::beg (comienzo del stream) 

	//Nota: verificar que el archivo de origen no termine en linea vacia, de lo contrario stod produce exepción
	//Asimismo que no haya una linea vacia entre datos

	cout << "Lectura:" << endl;
	do
	{
		auxiliar = 0;
		getline(data, temporal);
		array[contador] = stod(temporal, &auxiliar);
		cout << array[contador] << endl;
		contador++;
	} while (!data.eof());

	data.close();
	return array;
}

//Seleccion de la variable independiente 
void variable_dependiente(variables &V)
{
	int seleccion;
	double *aux;

	cout << "\nIngresar # de columna para seleccionar variable dependiente:\t";
	cin >> seleccion;

	switch (seleccion)
	{
	case 1:
		aux = V.z;
		V.z = V.x;
		V.x = V.y;
		V.y = aux;
		break;

	case 2:	//No revisado, seria un caso muy raro
		aux = V.z;
		V.z = V.y;
		V.y = aux;
		break;

	case 3:
		break;

	default:
		cout << "Error, se considerara la tercer columna como la variable dependiente" << endl;
	}
}
