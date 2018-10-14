#include "stdafx.h"
#include "Convertir.h"


Conver::Conver()
{
}


Conver::~Conver()
{
	cout << "Conversion finalizada" << endl;
	cout << "Destruyendo ..." << endl;
	system("pause");
}


void Conver::init()
{
	cout << "Ingresar cadena:\t";
	getline(cin, cadena);


	for (int i = 0; i < cadena.size(); i++)
	{
		int j, k;
		int reductor = 0;
		bool activ = false;

		//Nota: No cambiar de orden los siguientes enunciados:

		//Comportamiento del operador - para numeros negativos
		//Si el - esta al inicio de la cadena o despues de un (
		if (cadena[i] == '-')
		{
			if (i == 0 || cadena[i - 1] == '(')
			{
				//El valor del reductor influencia las evaluaciones en lectura de numeros y constantes
				reductor = 1;
				i++;
			}
		}

		//Cualquier grupo de caracteres numerico
		for (j = 0, k = i; numerico(cadena[k]) == true && k < cadena.size(); j++, k++, activ = true);

		if (activ == true)
		{
			postfija.push(cadena.substr(i - reductor, j + reductor));
			i += j;
		}

		//Cualquier constante arbitraria o expresion trigonometrica
		if (isalpha(cadena[i]))
		{
			bool evaluacion = trig_exp(cadena.substr(i, 3));

			if (evaluacion == false)
				postfija.push(cadena.substr(i - reductor, 1 + reductor));

			else
			{//Nota, revisar que pasa en este caso con el signo -
				pila.push(cadena.substr(i - reductor, 3 + reductor), 4);
				i += 3;
			}
		}


		//Comportamiento de operadores
		if (cadena[i] == '-')
			comparacion_operadores('-', 1, postfija, pila);


		if (cadena[i] == '+')
			comparacion_operadores('+', 1, postfija, pila);


		if (cadena[i] == '/')
			comparacion_operadores('/', 2, postfija, pila);


		if (cadena[i] == '*')
			comparacion_operadores('*', 2, postfija, pila);


		if (cadena[i] == '^')
			comparacion_operadores('^', 3, postfija, pila);


		if (cadena[i] == '(')
			pila.push("(", 0);


		if (cadena[i] == ')')
		{
			while (pila.top() != "(")
			{
				postfija.push(pila.top());
				pila.pop();
			}
			pila.pop();
		}


	}
	while (pila.vacia == false)
	{
		postfija.push(pila.top());
		pila.pop();
	}

	postfija.print();


	//Prueba
	cout<<endl;
	postfija.sustitucion();
	postfija.print();
	//Termina prueba

	
}


//Para clasificación de caracteres numericos
bool Conver::numerico(char x)
{
	switch (x)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
		return true;
	default:
		return false;
	}
}


/*
Proceso de comparacion_operadores
@param c	El  operador a comparar
@param p	Prioridad del operador
@param &a	postfija
@param &b	pila
*/
void Conver::comparacion_operadores(char c, int p, dual & a, dual & b)
{
	bool repetir;
	do
	{
		repetir = false;
		if (b.vacia == true)
			b.push(c, p);

		else
		{
			if (p > b.ptop())
			{
				b.push(c, p);
			}

			else
			{
				a.push(b.top());
				b.pop();
				repetir = true;
			}
		}

	} while (repetir == true);
}


//Evaluacion de expresiones especiales
bool Conver::trig_exp(string x)
{
	if (x == "exp")
		return true;

	else if (x == "sen" || x == "sin")
		return true;

	else if (x == "tan")
		return true;

	else if (x == "cos")
		return true;

	else return false;
}
