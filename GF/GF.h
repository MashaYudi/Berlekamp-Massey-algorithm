#pragma once
class GF
{
private:
	int power;
	int prim_poly;
	int* GF_Table;
	int* Log_Table;
public:
	~GF() {};
	GF(int p, int prim);

	int getLog(int i) {
		return Log_Table[i];
	}

	int getPower() {
		return power;
	}

	int getGF(int i) {
		return GF_Table[i];
	}
};