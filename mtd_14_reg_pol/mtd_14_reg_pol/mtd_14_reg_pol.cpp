// mtd_14_reg_pol.cpp: define el punto de entrada de la aplicación de consola.
// Regresion Polinomial
// Daniel Alejandro Rodríguez Castro	A01273096

//Notas de la versión: La lectura automatica se realiza con archivos separados para x y y
//Ya estan cargados en el proyecto dx.txt y dy.txt para aproximarse con un polinomio grado 2, del ejemplo visto en clase.


#include "stdafx.h"
#include <fstream>
#include <string>
#include "math.h"
#include "Mtd_Matriz.h"

double *lectura(int &contador);

int main()
{
	cout << "Regresion polinomial" << endl << endl;
	//Variables de datos
	double *valores_x = NULL;
	double *valores_y = NULL;
	int tam_x;
	int tam_y;
	bool seleccion;

	//Variables de proceso
	double **Matrix = NULL;
	double **Matriy = NULL;
	double **Mat_env = NULL;
	double *Sumas_x = NULL;
	double *Sumas_y = NULL;
	double *Regresion = NULL;
	double *valores_nuevos = NULL;
	int grado_m;

	//Ingreso de datos
	cout << "Ingresar datos manualmente?" << endl;
	cout << "[1]Si\t\t[0]No" << endl;
	cin >> seleccion;

	if (seleccion)
	{
		cout << "\nIngresar el numero de pares de datos x|y a registrar:\t";
		cin >> tam_x;
		tam_y = tam_x;

		valores_x = new double[tam_x];
		valores_y = new double[tam_y];

		cout << "\nIngresar valores de x" << endl;
		for (int i = 0; i < tam_x; i++)
		{
			cout << "x[" << i + 1 << "]:\t";
			cin >> valores_x[i];
		}

		cout << "\nIngresar valores de y" << endl;
		for (int i = 0; i < tam_x; i++)
		{
			cout << "y[" << i + 1 << "]:\t";
			cin >> valores_y[i];
		}
	}
	else
	{
		cout << "Lectura de datos x" << endl;
		valores_x = lectura(tam_x);
		cout << "Lectura de datos y" << endl;
		valores_y = lectura(tam_y);

		if (tam_x != tam_y)
		{
			cout << "Error, los pares de datos no coinciden\n";
			cout << "Verificar que haya la misma cantidad de datos para x, y" << endl;
			system("pause");
			exit(1);
		}
	}


	system("cls");


	//Proceso
	//Entrada de aproximación
	cout << "Grado del polinomio a aproximar?:\t";
	cin >> grado_m;


	//Creación de tablas auxiliares
	Matrix = new double *[tam_x];
	Matriy = new double *[tam_y];

	for (int i = 0; i < tam_x; i++)
	{
		Matrix[i] = new double[2 * grado_m + 1];
		Matriy[i] = new double[grado_m + 1];
	}

	for (int i = 0; i < tam_x; i++)
	{
		for (int j = 0; j <= 2 * grado_m; j++)
		{
			//El comportamiento de pow(0,0) ha sido definido = 1, asi que no hay que preocuparse cuando x=0
			Matrix[i][j] = pow(valores_x[i], j);
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl << endl;
	for (int i = 0; i < tam_y; i++)
	{
		for (int j = 0; j <= grado_m; j++)
		{
			Matriy[i][j] = Matrix[i][j] * valores_y[i];
			cout << Matriy[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;

	//system("pause");
	system("cls");

	//Sumatorias
	Sumas_x = new double[grado_m * 2 + 1];
	Sumas_y = new double[grado_m + 1];

	for (int i = 0; i <= grado_m * 2; i++)
		Sumas_x[i] = 0;

	for (int i = 0; i < grado_m + 1; i++)
		Sumas_y[i] = 0;

	for (int i = 0; i <= grado_m * 2; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			Sumas_x[i] += Matrix[j][i];
		}
		cout << Sumas_x[i] << endl;
	}

	for (int i = 0; i <= grado_m; i++)
	{
		for (int j = 0; j < tam_x; j++)
		{
			Sumas_y[i] += Matriy[j][i];
		}
		cout << Sumas_y[i] << endl;
	}

	//Conformación matriz para Gauss-Jordan y liberación de memoria parcial
	Mat_env = new double *[grado_m + 1];
	for (int i = 0; i < grado_m + 1; i++)
		Mat_env[i] = new double[grado_m + 2];


	for (int i = 0; i <= grado_m; i++)
	{
		for (int j = 0; j <= grado_m; j++)
		{
			Mat_env[i][j] = Sumas_x[j + i];
			cout << Mat_env[i][j] << "\t";
		}
		cout << endl;
	}

	for (int i = 0; i <= grado_m; i++)
	{
		Mat_env[i][grado_m + 1] = Sumas_y[i];
		cout << Mat_env[i][grado_m + 1] << endl;
	}

	//Liberación 
	for (int i = 0; i < tam_x; i++)
	{
		delete[] Matrix[i];
		delete[] Matriy[i];
	}
	delete[] Matrix;
	delete[] Matriy;
	system("cls");


	//Gauss-Jordan
	cout << "Aplicando metodo de Gauss-Jordan" << endl;
	Mtd_Matriz *solucion = new Mtd_Matriz(Mat_env, grado_m + 1, grado_m + 2);
	solucion->imprimir();
	solucion->Gauss_Jordan();
	solucion->imprimir();
	Regresion = solucion->retornar_soluciones();

	//Funcion resultante
	cout << "\nFuncion resultante:" << endl;
	cout << "y^ =";
	for (int i = 0; i < grado_m + 1; i++)
		cout << "\t"<<Regresion[i]<<"x^" << i;
	cout << endl;

	//Nuevos valores
	valores_nuevos = new double[tam_x];

	for (int i = 0; i < tam_x; i++)
		valores_nuevos[i] = 0;

	for (int i = 0; i < tam_x; i++)
	{
		for (int j = 0; j <= grado_m; j++)
			valores_nuevos[i] += pow(valores_x[i], j) * Regresion[j];
		
	}
	
	//Impresión
	cout << endl << "Resultados:" << endl << endl;
	cout << "\tx\ty\ty^" << endl;
	for (int i = 0; i < tam_x; i++)
		cout << i + 1 << "\t" << valores_x[i] << "\t" << valores_y[i] << "\t" << valores_nuevos[i] << endl;


	//Liberación de memoria completa
	delete[] valores_x, valores_y, Regresion, solucion, valores_nuevos, Sumas_x, Sumas_y;
	cin.get();
	cin.get();
}

/*
Lectura automatica de datos en un fichero de texto
*/
double *lectura(int &contador)
{
	string archivo;
	string temporal;
	contador=0;
	size_t auxiliar;

	cout << "Ingresar archivo de origen de datos:\t";
	cin >> archivo;
	
	ifstream data;
	data.open(archivo, ios::in);			//ios::in Bandera de operaciones de entrada

	if (data.fail())
	{
		cout << "Error, no se pudo abrir el archivo " << archivo << endl;
		system("pause");
		exit(1);
	}

	while (!data.eof())			//Bloque para determinar el tamaño del arreglo dinámico
	{							//!eof Mientras no haya terminado el archivo
		getline(data,temporal);
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

//Errores detectados
//Si hay lineas vacias la lectura automatica falla.
//Si hay un salto de linea al final del archivo la lectura automatica falla.
