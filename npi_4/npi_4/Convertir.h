#pragma once
#include "dual.h"
class Conver
{
public:
	Conver();
	~Conver();
	void init();


	vector<string> dir()
	{
		return postfija.copy();
	}


private:
	string cadena;
	dual postfija;
	dual pila;
	bool numerico(char x);
	void comparacion_operadores(char c, int p, dual &a, dual &b);
	bool trig_exp(string x);
};

