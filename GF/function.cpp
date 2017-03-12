#pragma once
#include "GF.h"
int mult(const int a, const int b, GF* field)
{
	if ((field->getLog(b) == -1) || (field->getLog(a) == -1))
	{
		return 0;
	}
	else
	{
		int m = ((field->getLog(a)) + (field->getLog(b))) % ((1 << field->getPower()) - 1);
		return field->getGF(m + 1);
	}
}
int rev(int a, GF* galua) {
	if (a == 1)
		return a;
	int rev = galua->getGF((1 << galua->getPower()) - galua->getLog(a));
	return rev;
}
int power(int a, int b, GF* galua) {
	int m = ((galua->getLog(a))*b) % ((1 << galua->getPower()) - 1);
	return galua->getGF(m + 1);
}