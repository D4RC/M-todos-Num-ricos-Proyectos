// mtd_16_reg_lin_mul_ex.cpp 

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>		
#include "Mtd_Matriz.h"

using namespace std;

struct datos {
	double **v;	//variables
	int num=0;	//número de variables
	int tam=0;	//número de datos de cada variable
};

void lectura_multiple_ex(datos &V);
void seleccion_variable(datos &V);

int main()
{
	datos V;
	double *sumas_=NULL, *sumas_yx=NULL, **sumas_xx=NULL;
	double **M = NULL;

	cout << "Regresión Lineal Multiple" << endl;
	cout << "Funcion de n variables\t\ty=" << char(159) << "(x_1,x_2, ... ,x_n)" << endl;

	//Lectura de datos
	lectura_multiple_ex(V);

	//Seleccion de variable dependiente
	seleccion_variable(V);

	//Reservación de espacio e inicialización a 0
	sumas_ = new double[V.num];
	sumas_yx = new double[V.num - 1];
	sumas_xx = new double *[V.num - 1];

	for (int i = 0; i < V.num; i++)
		sumas_[i] = 0;
	for (int i = 0; i < V.num - 1; i++)
		sumas_yx[i] = 0;

	for (int i = 0; i < V.num - 1; i++)
	{
		sumas_xx[i] = new double[V.num - 1];

		for (int j = 0; j < V.num - 1; j++)
			sumas_xx[i][j] = 0;
	}
	
	//Proceso

	//Sumatorias
	for (int i = 0; i < V.num; i++)
		for (int j = 0; j < V.tam; j++)
			sumas_[i] += V.v[i][j];

	for (int i = 0; i < V.num-1; i++)
		for (int j = 0; j < V.tam; j++)
			sumas_yx[i] += V.v[0][j] * V.v[i + 1][j];

	for (int i = 0; i < V.num - 1; i++)
		for (int j = 0; j < V.num - 1; j++)
			for (int k = 0; k < V.tam; k++)
				sumas_xx[i][j] += V.v[i + 1][k] * V.v[j + 1][k];
			
		
	//Elaboración de matriz
	M = new double *[V.num];

	for (int i = 0; i < V.num; i++)
		M[i] = new double[V.num + 1];
	M[0][0] = V.tam;
	M[0][V.num] = sumas_[0];

	for (int i = 1; i < V.num; i++)
	{
		M[0][i] = sumas_[i];
		M[i][0] = sumas_[i];
	}

	for (int i = 1; i < V.num; i++)
		M[i][V.num] = sumas_yx[i - 1];
	
	for (int i = 1; i < V.num; i++)
		for (int j = 1; j < V.num; j++)
			M[i][j] = sumas_xx[i - 1][j - 1];


	//Gauss-Jordan
	Mtd_Matriz *sol = new Mtd_Matriz(M, V.num, V.num+1);
	sol->imprimir();
	sol->Gauss_Jordan();
	sol->imprimir();
	
	double *soluciones;
	soluciones = sol->retornar_soluciones();





	//Liberación de memoria
	for (int i = 0; i < V.num; i++)
		delete[] V.v[i];
	delete[] V.v;

	for (int i = 0; i < V.num - 1; i++)
		delete[] sumas_xx[i];
	delete[] sumas_xx;

	delete[] sumas_yx, sumas_;

	delete sol;
}


void lectura_multiple_ex(datos &V)
{
	string archivo, temporal;

	cout << "Ingresar archivo de origen de datos:\t";
	cin >> archivo;

	ifstream data;
	data.open(archivo, ios::in);			//ios::in Bandera modo de entrada

	if (data.fail())
	{
		cout << "No se pudo abrir el archivo " << archivo << endl;
		cout << "Ingresar correctamente el nombre del archivo con su extension" << endl;
		cout << "Verificar que este en la carpeta del proyecto o anadir su ubicacion" << endl;
		system("pause");
		exit(1);
	}


	char delimitador = '\t';				//Por defecto el delimitador lo estableci como el tabulador, cambiar si es necesario
	size_t encontrar;						//Se cambiara automaticamente a una ',' si el archivo es un csv
	encontrar = archivo.rfind(".csv");		//npos se retorna si no se encontro coincidencia
	if (encontrar != string::npos)		
		delimitador = ',';

	while (!data.eof())						//Determinando el tamaño de arreglos dinámicos para cada variable
	{
		getline(data, temporal);
		V.tam++;
	}

	stringstream individual(temporal);		//Determinando el número de variables
	while (getline(individual, temporal, delimitador))	
	{
		V.num++;
	}

	//Creación de arreglos dinámicos
	V.v = new double *[V.num];				//New para cada variable

	for (int i = 0; i < V.num; i++)		
		V.v[i] = new double[V.tam];			//New para datos de cada variable


	data.clear();				//Limpieza de banderas
	data.seekg(0, ios::beg);	//Restaurar a posicion 0 en relacion a ios::beg (comienzo del stream) 


	//Nota: verificar que el archivo de origen no termine en linea vacia, de lo contrario stod produce exepción
	//Asimismo que no haya una linea vacia entre datos

	cout << "Lectura:" << endl;

	for (int i = 0; !data.eof(); i++)
	{
		getline(data, temporal);
		stringstream individual(temporal);

		for (int j=0; getline(individual, temporal, delimitador); j++)	//La extracción del getline tambien termina si la linea acaba
		{																//Por eso no es necesario especificar el delimitador \n en este caso
			V.v[j][i] = stod(temporal, NULL);
			cout << V.v[j][i] << "\t";
		}
		cout << endl;
	}

	data.close();
}

void seleccion_variable(datos &V)
{
	bool seleccion;
	cout << "Seleccion de la variable dependiente:" << endl;
	cout << "Default:	Primer columna" << endl;
	cout << char(168) << "Intercambiar?:\t[1]Si\t[0]No:\t";
	cin >> seleccion;

	int sel;
	double *temp;
	double *aux;

	if (seleccion)
	{
		cout << "Se encontaron " << V.num << " variables (" << V.num << " columnas)" << endl;
		cout << "Seleccionar columna de datos de la variable dependiente:\t";
		cin >> sel;
		if (sel > V.num || sel <= 0)
		{
			cout << "Error, rango no valido, reiniciar";
			system("pause");
			exit(1);
		}

		cout << "Se ha seleccionado la columna " << sel << " como variable dependiente" << endl;
		temp = V.v[0];
		aux = V.v[sel - 1];
		V.v[0] = aux;
		V.v[sel - 1] = temp;

		/*
		cout << char(168) << "\nIntercambiar columnas de las variables indepenstientes?:\t[1]Si\t[0]No:\t";
		cin >> seleccion;

		if (seleccion)
		{
		}
		*/
	}

	cout << "Configuracion actual:\n\n";
	for (int i = 1; i < V.num; i++)
		cout << "x" << i << "\t";
	cout << "y" << endl;

	for (int i = 0; i < V.tam; i++)
	{
		for (int j = 1; j < V.num; j++)
			cout << V.v[j][i] << "\t";
		cout << V.v[0][i] << endl;
	}
	cout << endl;
}