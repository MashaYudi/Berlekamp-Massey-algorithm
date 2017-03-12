#pragma once
#include "GF_Vector.h"
#include "func_header.h"
using namespace std;
GF_Vector::GF_Vector(GF* _gf, int size, int const*const element) {
	gf = _gf;
	vector.resize(size);
	if (element != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			vector.at(i) = element[i];
		}
	}
	else
	{
		for (int i = 0; i < vector.size(); i++)
		{
			vector[i] = 0;
		}
	}
}

//GF_Vector::GF_Vector(const  int size, Elem* element)
//{
//	gf = element->get_gf();
//	vector.resize(size);
//
//	if (element != NULL)
//	{
//		for(int i = 0; i < size; i++)
//		{
//			this->vector[i] = element[i];
//		}
//	}
//	else
//	{
//		for(int i = 0; i < vector.size(); i++)
//		{
//			vector[i] = Elem(0,gf);
//		}
//	}
//
//}

//GF_Vector::GF_Vector(GF* _gf, const  int size, int* element)
//{
//	gf = _gf;
//
//	vector.resize(size);
//
//	if (element != NULL)
//	{
//		for(int i = 0; i < size; i++)
//		{
//			vector[i] = element[i];
//		}
//	}
//	else
//	{
//		for(int i = 0; i < vector.size(); i++)
//		{
//			vector[i] = 0;
//		}
//	}
//
//}

GF_Vector::GF_Vector(const GF_Vector& polynomial)
{
	gf = polynomial.gf;
	vector = polynomial.vector;
}

GF_Vector GF_Vector::operator*(const GF_Vector& polynomial) {
	GF_Vector result(gf, deg() + polynomial.deg() + 1);
	if (gf == polynomial.gf)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			for (int j = 0; j < polynomial.vector.size(); j++)
			{
				//result.vector[i + j] = result.vector[i + j] ^ mult(vector[i], polynomial.vector[j], gf);
				if ((vector[i] != 0) && (polynomial.vector[j] != 0))
				{
					int m = ((gf->getLog(vector[i])) + (gf->getLog(polynomial.vector[j]))) % ((1 << gf->getPower()) - 1);
					result.vector[i + j] = result.vector[i + j] ^ gf->getGF(m + 1);
				}
			}
		}
	}
	return result;
}

//GF_Vector GF_Vector::operator* (int poly) {
//	GF_Vector result(gf, deg() + 1);
//	for (int i = 0; i < vector.size(); i++)
//	{
//		result.vector[i] = mult(vector[i], poly, gf);
//	}
//	return result;
//}

GF_Vector& GF_Vector::operator*=(const GF_Vector& polynomial)
{
	int m;
	if (gf == polynomial.gf)
	{
		GF_Vector result(gf, deg() + polynomial.deg() + 1);
		for (int i = 0; i < vector.size(); i++)
		{
			for (int j = 0; j < polynomial.vector.size(); j++)
			{
				//result.vector[i + j] = result.vector[i + j] ^ mult(vector[i], polynomial.vector[j], gf);
				if ((vector[i] != 0) && (polynomial.vector[j] != 0))
				{
					m = ((gf->getLog(vector[i])) + (gf->getLog(polynomial.vector[j]))) % ((1 << gf->getPower()) - 1);
					result.vector[i + j] = result.vector[i + j] ^ (gf->getGF(m + 1));
				}

			}
		}

		vector = result.vector;
	}
	return *this;
}

GF_Vector GF_Vector::operator+(GF_Vector& add) {
	if (vector.size() < add.vector.size())
		return add + *this;
	GF_Vector result(gf, fmax(deg(), add.deg()) + 1);
	if (gf == add.gf) {

		for (int i = 0; i < result.vector.size(); i++)
		{
			result.vector[i] = vector[i] ^ (i < add.vector.size() ? add.vector[i] : 0);
		}
	}
	return result;
}

GF_Vector GF_Vector::operator=(GF_Vector& snd) {
	gf = snd.gf;
	vector = snd.vector;
	return *this;
}

int GF_Vector::operator[](int index) const {
	return vector.at(index);
}

int& GF_Vector::operator[](int index) {
	return vector.at(index);
}

int GF_Vector::deg() const
{
	return (vector.size() - 1);
}

int GF_Vector::get(int i) {
	return this->vector[i];
}

ostream& operator << (ostream& out, GF_Vector& polynomial)
{
	if (polynomial.deg() >= 0)
	{
		for (unsigned int i = 0; i < polynomial.vector.size(); i++)
		{
			out << polynomial.vector[i] << " ";
			/*<< "x^"
			<< i
			<< ((i != (polynomial.deg())) ? " + " : "");*/
		}
	}
	cout << endl;
	return out;
}

int GF_Vector::reduce(int elem, GF* gf) {
	int p = 0;
	int m;
	for (int i = this->getSize() - 1; i >= 0; i--)
	{
		//p = mult(p, elem, gf) ^ this->vector[i];
		if ((p == 0) || (elem == 0)) {
			p = this->vector[i];
		}
		else
		{
			m = ((gf->getLog(p)) + (gf->getLog(elem))) % ((1 << gf->getPower()) - 1);
			p = gf->getGF(m + 1) ^ this->vector[i];
		}
	}
	return p;
}
//GF_Vector& GF_Vector::operator%=(const GF_Vector& div)// div - делитель
//{
//	if (
//		(gf == div.gf) &&
//		(deg() >= div.deg()) &&
//		(div.deg() >= 0)
//		)
//	{
//		GF_Vector  quotient(gf, deg() - div.deg() + 1);// частное
//		GF_Vector remainder(gf, div.deg() - 1);// остаток
//
//		for (int i = deg(); i >= 0; i--)
//		{
//			if (i <= quotient.deg())
//			{
//				int rev = gf->getGF((1 << gf->getPower()) - gf->getLog(div.vector[div.deg()]));
//				quotient.vector[i] = mult(remainder.vector[remainder.deg()], rev, gf);
//
//				for (int j = remainder.deg(); j > 0; j--)
//				{
//					remainder.vector[j] = remainder.vector[j - 1] ^ mult(quotient.vector[i], div.vector[j], gf);
//				}
//				remainder.vector[0] = vector[i] ^ mult(quotient.vector[i], div.vector[0], gf);
//			}
//			else
//			{
//				for (int j = remainder.deg(); j > 0; j--)
//				{
//					remainder.vector[j] = remainder.vector[j - 1];
//				}
//				remainder.vector[0] = vector[i];
//			}
//		}
//		vector = remainder.vector;
//	}
//	return *this;
//}
bool GF_Vector::operator==(const GF_Vector& polynomial) const
{
	if (gf == polynomial.gf)
	{
		if (vector.size() != polynomial.vector.size())
			return false;
		else
		{
			for (unsigned int i = 0; i < vector.size(); i++)
			{
				if (vector[i] != polynomial.vector[i])
					return false;
			}
			return true;
		}
	}
	else
		return false;
}







