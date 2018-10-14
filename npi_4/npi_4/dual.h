#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class dual
{
private:
	vector<string> expresion;
	vector<int> prioridad;
	

public:
	static const char variable_independiente = 'x';


	dual();
	~dual();

	bool vacia;
	void push(string x);
	void push(string x, int prioridad);
	void push(char x, int y);
	void pop();
	void print();
	int ptop();

	string top();
	string at(int x);
	
	size_t tamaño_expresion();
	void transforma(int x, string w);
	void sustitucion();
	vector<string> copy();
};
