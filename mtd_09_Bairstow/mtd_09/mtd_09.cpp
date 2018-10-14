
#include "stdafx.h"
#include <iostream>
#include "math.h"
#include "Equation.h"


using namespace std;

void almacenamiento(double *polinomio, int grado);
void almacenamiento(double *polinomio, CEquation cociente, int &grado);
void recurrencia(int grado, double *pol_a, double *pol_b, double *pol_c, double r, double s);
void traspolacion(double &D_s, double &D_r, double *b, double *c);
void cuadratica(double *res, int &cont, double r, double s);
void division_polinomio(double *a, double *div, int grado, CEquation &quotient);
void cuadratica(double *res, CEquation cociente, int &contador);

void main()
{
	//Composición del polinomio
	int grado;
	double *polinomio_a = NULL;

	//Errores
	double Ea_r, Ea_s;

	//Iteracion 
	int max_it;
	int iteracion=0;

	//Polinomios auxiliares
	double *polinomio_b = NULL, *polinomio_c = NULL;

	//Valores iniciales
	double r, s;

	//Diferenciales r y s
	double D_s, D_r;

	//Raices
	double *resultado = NULL;
	int contador=0;

	//Cociente de division polinomial
	CEquation cociente;

	//Arreglo almacenamiento de respuestas
	cout << "Grado de la ecuacion:\t";
	cin >> grado;
	resultado = new double[grado];

	cout << "Limite de iteraciones:\t";
	cin >> max_it;

	cout << "Valores iniciales" << endl;
	cout << "r:\t";
	cin >> r;
	cout << "s:\t";
	cin >> s;


	do
	{
		polinomio_a = new double[grado+1];
		(iteracion==0)?almacenamiento(polinomio_a, grado):almacenamiento(polinomio_a, cociente, grado);
		polinomio_b = new double[grado+1];
		polinomio_c = new double[grado];

		do {
			recurrencia(grado, polinomio_a, polinomio_b, polinomio_c, r, s);
			traspolacion(D_s, D_r, polinomio_b, polinomio_c);

			//Incremento r y s
			r += D_r;
			s += D_s;

			//Calculo de error
			Ea_r = abs(D_r / r) * 100;
			Ea_s = abs(D_s / s) * 100;
			iteracion++;
		} while ((Ea_r >= 0 || Ea_s >= 0) && iteracion<=max_it);

		//Cuadratica bairstow
		cuadratica(resultado, contador, r, s);

		//Conformacion de polinomio divisor
		double auxiliar[3];
		auxiliar[2] = 1;
		auxiliar[1] = -r;
		auxiliar[0] = -s;

		division_polinomio(polinomio_a, auxiliar, grado, cociente);
		

		delete[] polinomio_a, polinomio_b, polinomio_c;
	} while (cociente.grade >= 3);

	//Formula general
	if (cociente.grade == 2)
		cuadratica(resultado, cociente, contador);
	else
	{
		resultado[contador] = -cociente.data[0] / cociente.data[1];
		contador++;
	}

	for (int i = 0; i < contador; i++)
		cout << "Raiz:\t" << resultado[i] << endl;

	cin.get();
	cin.get();
		
		//Liberacion
		delete[] resultado;
}

void almacenamiento(double *polinomio, int grado)
{
	cout << "Ingresar polinomio:" << endl;
	for (int i = grado; i >= 0; i--)
	{
		cout << "Coeficiente de x^" << i << ":\t";
		cin >> polinomio[i];
	}
}

//Sobrecarga para iteracion !=0
void almacenamiento(double *polinomio, CEquation cociente, int &grado)
{
	grado = cociente.grade;
	for (int i = cociente.grade; i <= 0; i++)
	{
		polinomio[i] = cociente.data[i];
	}
}

void recurrencia(int grado, double *pol_a, double *pol_b, double *pol_c, double r, double s)
{
	int n = grado;
	pol_b[n] = pol_a[n];
	pol_b[n - 1] = pol_a[n - 1] + r * pol_b[n];

	pol_c[n] = pol_b[n];
	pol_c[n - 1] = pol_b[n - 1] + r * pol_c[n];


	for (int j = n - 2; j >= 0; j--)
		pol_b[j] = pol_a[j] + r * pol_b[j + 1] + s * pol_b[j + 2];

	for (int k = n - 2; k >= 1; k--)
		pol_c[k] = pol_b[k] + r * pol_c[k + 1] + s * pol_c[k + 2];
}

void traspolacion(double &D_s, double &D_r, double *b, double *c)
{
	D_r = (b[0] * c[3] - b[1] * c[2]) / (pow(c[2], 2) - c[1] * c[3]);
	D_s = (b[1] * c[1] - b[0] * c[2]) / (pow(c[2], 2) - c[1] * c[3]);
}

//Revisar para numeros complejos
void cuadratica(double *res, int &cont, double r, double s)
{
	res[cont] = (r + sqrt(pow(r, 2) + 4 * s)) / 2;
	cont++;

	res[cont] = (r - sqrt(pow(r, 2) + 4 * s)) / 2;
	cont++;
}
//Sobrecarga formula general
void cuadratica(double *res, CEquation cociente, int &cont)
{
	double a = cociente.data[2];
	double b = cociente.data[1];
	double c = cociente.data[0];

	res[cont] = (-b + sqrt(pow(b, 2) - 4 * a*c)) / 2 * a;
	cont++;

	res[cont] = (-b - sqrt(pow(b, 2) - 4 * a*c)) / 2 * a;
	cont++;
}

void division_polinomio(double *a, double *div, int grado, CEquation &quotient)
{
		CEquation divisor;
		CEquation dividend;
	
		dividend.storage(a, grado);
		divisor.storage(div, 2);//Modificado en esta ocasion siempre divide entre polinomio grado 2
		

		//Arreglo para almacenar el resultado
		quotient.grade = dividend.grade - divisor.grade;

		//Almacenamiento temporal del dividendo(Para efectuar bloques de división)
		dividend.temporal_storage();
		quotient.counter = quotient.grade;

		do
		{
			//Factor de división(Cada termino del cociente)
			double max_div;
			max_div = dividend.temporal[dividend.counter] / divisor.data[divisor.grade];

			//Almacenamiento de cociente
			quotient.data[quotient.counter] = max_div;
			quotient.counter--;

			//Bloque de división
			for (int i = divisor.grade, j = dividend.counter; i >= 0; i--, j--)
				dividend.temporal[j] -= divisor.data[i] * max_div;
			dividend.counter--;

		} while (dividend.counter >= quotient.grade);
}
