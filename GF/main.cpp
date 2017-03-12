#pragma once
#include <iostream>
#include "vector"
#include "GF.h"
#include "GF_Vector.h"
GF_Vector RS(int t, int j_0, GF *field);
void BM(GF *field, int j_0, int t, GF_Vector v);
using namespace std;
int main() {
	string s;
	int m, t, j_0 = 1, k, l;
	int prim_poly[11];
	prim_poly[0] = 7;
	prim_poly[1] = 11;
	prim_poly[2] = 19;
	prim_poly[3] = 37;
	prim_poly[4] = 67;
	prim_poly[5] = 137;
	prim_poly[6] = 285;
	prim_poly[7] = 529;
	prim_poly[8] = 1033;
	cout << "Enter 'm':";
	cin >> m;
	GF field(m, prim_poly[m - 2]);
	while (true) {
		//cout << "Enter 'j_0':";
		//cin >> j_0;
		cout << "Enter 't':";
		cin >> t;
		k = (1 << field.getPower()) - 1 - 2 * t;
		if (k < 0) {
			cout << "'t' parameter's too big" << endl;
			continue;
		}
		int *inf = new int[k];
		cout << "Enter coeffs" << endl;
		for (int i = 0; i < k; i++) {
			cout << "x^" << i << " : ";
			cin >> inf[i];
		}
		GF_Vector g(&field);
		GF_Vector v(&field);
		GF_Vector i(&field, k, inf);
		g = RS(t, j_0, &field);
		v = g*i;
		cout << "inf: " << endl;
		cout << v << endl;
		cout << "enter number of errors" << endl;
		cin >> l;
		for (int i = 0; i < l; i++) {
			int q;
			cout << "enter place: ";
			cin >> q;
			cout << "enter value: ";
			cin >> v[q];
		}
		BM(&field, j_0, t, v);
		delete[] inf;
		cout << "---------------------------------------------------" << endl;
	}
	return 0;
}