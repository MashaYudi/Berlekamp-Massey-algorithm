#pragma once
#include <iostream>
#include "GF.h"
#include "vector"
using namespace std;
class GF_Vector
{
private:
	GF* gf;
	vector<int> vector;
public:
	GF_Vector(GF* _gf = NULL, const int size = 0, int const*const element = NULL);
	GF_Vector(const GF_Vector& poly);
	~GF_Vector() {};

	GF_Vector& operator*= (const GF_Vector& poly);
	GF_Vector operator* (const GF_Vector& poly);
	//GF_Vector operator* (int poly);
	//GF_Vector& operator%=(const GF_Vector& div);
	GF_Vector operator+ (GF_Vector& add);
	GF_Vector operator=(GF_Vector& snd);
	bool operator==(const GF_Vector& poly) const;
	int operator[](int index) const;
	int& operator[](int index);

	int get(int i);
	int deg() const;
	int reduce(int elem, GF* gf);
	void resize(int i) {
		this->vector.resize(i);
	};
	int getSize() {
		return vector.size();
	};
	friend ostream& operator << (ostream& out, GF_Vector& poly);
};

