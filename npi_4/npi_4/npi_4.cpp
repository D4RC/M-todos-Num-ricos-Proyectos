// npi_4.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Convertir.h"
#include "Evaluar.h"


void main()
{
	Conver *principal = new Conver();
	principal->init();
	Eval *ecuacion = new Eval(*principal);
	delete principal;
	cout<<ecuacion->Evaluacion();
	cin.get();
	cin.get();
	delete ecuacion;
}