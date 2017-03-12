#pragma once
#include <iostream>
#include "GF_Vector.h"
//int power (int a, int b, GF* galua);
using namespace std;
GF_Vector RS(int t, int j_0, GF *field){
	int prim = 2;
	int log_2 = field->getLog(prim);
	int a_j;
	GF_Vector mult(field, 2);
	GF_Vector g(field, 2);
	mult[1] = 1;
	g[1] = 1;
	//g[0] = power(prim, j_0 ,field);

	int m = ((field->getLog(prim))*j_0) % ((1 << field->getPower()) - 1);
	g[0] = field->getGF(m + 1);

	for(int i = 1; i<2*t; i++){ 
		//a_j = power(prim,(j_0+i),field);
		m = (log_2*(j_0 + i)) % ((1 << field->getPower()) - 1);
		a_j = field->getGF(m + 1);
		mult[0] = a_j;
		g *= mult;
		}
	cout<<"g = "<<g<<endl;
	return g;
	}