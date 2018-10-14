#include "stdafx.h"
#include "dual.h"


dual::dual()
{
	vacia = true;
}

dual::~dual()
{
}

void dual::push(string x)
{
	expresion.push_back(x);
	vacia = false;
}

void dual::print()
{
	for (int i = 0; i<expresion.size(); i++)
		cout << expresion[i] << "\t";
}

//Sobrecarga para introducir con prioridades
void dual::push(string x, int y)
{
	expresion.push_back(x);
	prioridad.push_back(y);
	vacia = false;
}

//Sobrecarga para introducir con prioridades y un solo caracter
void dual::push(char x, int y)
{
	string auxiliar;
	auxiliar += x;
	expresion.push_back(auxiliar);
	prioridad.push_back(y);
	vacia = false;
}

void dual::pop()
{
	expresion.pop_back();
	vacia = expresion.empty();

	//En caso de que la expresion este vacia no puede sacar de prioridad
	if (vacia == false)
		prioridad.pop_back();
}

string dual::top()
{
	return expresion.back();
}

int dual::ptop()
{
	return prioridad.back();
}


void dual::sustitucion()
{
	for (int i = 0; i < expresion.size(); i++)
		if (isalpha(expresion[i].back()))			//Exclusión de signos
			if (expresion[i].size() <= 2 && expresion[i].back() != variable_independiente)	//Exclusion de identidades y variable independiente
			{
			char busqueda = expresion[i].back();
			double intercambio;

			cout << "Valor de la constante " << expresion[i].back() << "?:\t";
			cin >> intercambio;


			for (int j = 0; j < expresion.size(); j++)
			{
				//Sustitución;
				if (expresion[j].back() == busqueda && expresion[j].size() <= 2)
				{
					expresion[j].pop_back();
					string cambio;
					cambio = to_string(intercambio);
					expresion[j] += cambio;
				}
			}
			}
}

vector<string> dual::copy()
{
	return expresion;
}


//Tamaño del vector expresion
size_t dual::tamaño_expresion()
{
	return sizeof(expresion);
}

//Intercambia un elemento de la expresion
void dual::transforma(int x, string w)
{
	expresion[x]=w;
}

string dual::at(int x)
{
	return expresion[x];
}