// mtd_11_Reg_lineal.cpp: define el punto de entrada de la aplicación de consola.
// Regresion Lineal
// Daniel Alejandro Rodríguez Castro									A01273096

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "math.h"

using namespace std;

double *lectura(int &contador);
double suma(double *a, int b);
void escritura(double *x, double *y, double *rl, int tam);

int main()
{
	cout << "Regresion Lineal" << endl << endl;

	//Variables de datos
	double *valores_x=NULL;
	double *valores_y=NULL;
	int tam_x;
	int tam_y;
	bool seleccion;

	//Variables de proceso
	double media_x, media_y;
	double *diferencias = NULL;
	double Stx;
	double *xi_yi = NULL;
	double a, b;
	double *Regresion_lin = NULL;
	double covarianza;
	double varianza_x;

	//Ingreso de datos
	cout << "Ingresar datos manualmente?" << endl;
	cout << "[1]Si\t\t[0]No" << endl;
	cin >> seleccion;

	if (seleccion == true)
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
	
	//Proceso
	//Media
	media_x = suma(valores_x, tam_x)/tam_x;
	media_y = suma(valores_y, tam_y)/tam_y;

	//Stx
	diferencias = new double[tam_x];
	for (int i = 0; i < tam_x; i++)
		diferencias[i] = pow(valores_x[i] - media_x, 2);

	Stx = suma(diferencias, tam_x);

	//Varianza x
	varianza_x = Stx / (tam_x - 1);

	//xi*yi
	xi_yi = new double[tam_x];
	for (int i = 0; i < tam_x; i++)
		xi_yi[i] = valores_x[i] * valores_y[i];

	//Covarianza
	covarianza = suma(xi_yi, tam_x) / tam_x - media_x * media_y;

	//a y b
	b = covarianza / varianza_x;
	a = media_y - b * media_x;

	//Recta a+bx
	Regresion_lin = new double[tam_x];
	for (int i = 0; i < tam_x; i++)
		Regresion_lin[i] = a + b * valores_x[i];

	system("cls");

	//Impresion
	cout << "\tx\ty\ty^" << endl;
	for (int i = 0; i < tam_x; i++)
		cout << i + 1 << "\t" << valores_x[i] << "\t" << valores_y[i] << "\t" << Regresion_lin[i] << endl;

	cout << endl << endl;
	cout << "a:\t" << a << endl;
	cout << "b:\t" << b << endl;

	cout << "\ny^ = " << a << "x + " << b << endl << endl;

	//Escritura
	cout << endl << endl;
	cout << "Guardar los datos?" << endl;
	cout << "[1]Si\t\t[0]No" << endl;
	cin >> seleccion;

	if (seleccion == true)
		escritura(valores_x, valores_y, Regresion_lin, tam_x);

	//Predicciones		(Deshabilitado, me parecio innecesario)
	/*
	cout << endl << endl;
	cout << "Hacer una prediccion?" << endl;
	cout << "[1]Si\t\t[0]No" << endl;
	cin >> seleccion;

	while(seleccion==true)
	{
		double tem_x, prediccion;

		cout << "Ingresar valor x:\t";
		cin >> tem_x;

		prediccion = a * tem_x + b;
		cout << "y^=\t" << prediccion << endl;

		cout << endl;
		cout << "Realizar otra? [1]Si [0]No:\t";
		cin >> seleccion;
	}
	*/

	//Liberación de memoria
	delete[] valores_x, valores_y, xi_yi, diferencias, Regresion_lin;
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

/*
Escritura automatica en un fichero de texto
@param x Puntero a arreglo de valores x
@param y Puntero a arreglo de valores y
@param rl Puntero a arreglo de valores de la regresión lineal
@param tam Tamaño de cualquiera de los arreglos previos
*/
void escritura(double *x, double *y, double *rl, int tam)
{
	string archivo;

	cout << "Ingresar nombre del archivo:" << endl;
	cin.ignore();				//Ignorar el buffer de entrada
	getline(cin, archivo);

	ofstream data;

	data.open(archivo.c_str(), ios::out);

	if (data.fail())
	{
		cout << "Error en la creacion del archivo" << endl;
		system("pause");
		exit(1);
	}

	data << "x\ty\ty^" << endl;

	for (int i = 0; i < tam; i++)
	{
		data << x[i] << "\t" << y[i] << "\t" << rl[i] << endl;
	}

	data.close();

	cout << "Finalizado, datos escritos en la carpeta del proyecto" << endl;
}

/*
Retorna la suma de los elementos en un arreglo
@param a Puntero a arreglo
@param b Tamaño del arreglo
*/
double suma(double *a, int b)
{
	double sum = 0;
	for (int i = 0; i < b; i++)
		sum += a[i];
	
	return sum;
}

/*
Notas:
La automatica no ha generado ningun problema, aparte del de las lineas vacias 
El comportamiento del bool seleccion esta indefinido al insertar algo diferente de 0 o 1

Pendientes:
Implementar verificación por el coeficiente de correlación
Implementar control de exepciones
*/