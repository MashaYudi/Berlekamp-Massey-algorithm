#include "GF.h"
#include <math.h>
GF::GF(int m, int prim)
{
	power = m;
	prim_poly = prim;
	int n = (int)pow(2.0, power);
	GF_Table = new int[n];
	GF_Table[0] = 0;
	GF_Table[1] = 1;
	for (int i = 2; i < n; i++) {
		GF_Table[i] = GF_Table[i - 1] * 2;
		if (GF_Table[i] > (n - 1))
			GF_Table[i] = GF_Table[i] ^ prim_poly;
	}
	Log_Table = new int[n];
	for (int i = 0; i < n; i++) {
		Log_Table[GF_Table[i]] = i - 1;

	}

}