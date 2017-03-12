#include <iostream>
#include "GF_Vector.h"
#include "func_header.h"
#include <time.h> 
using namespace std;
void BM(GF *field, int j_0, int t, GF_Vector v) {
	int m, counter = 0;
	int rev_var, mult_var, power_var, reduce_var = 0;
	int one = 1, delta = 0, primitive = 2;
	int sizeOfField = (1 << field->getPower()) - 1;
	int x[2] = { 0,1 };
	GF_Vector T(field);
	GF_Vector X(field, 2, x);
	GF_Vector B(field, 1, &one);
	GF_Vector temp(field);
	GF_Vector posit(field);
	GF_Vector lambda(field, 1, &one);

	cout << "what we got: " << endl;
	cout << v << endl;

	//Syndrome calculation

	int log_2 = field->getLog(primitive);
	GF_Vector S(field, 2 * t+1);
	for (int i = 0; i < 2 * t; i++) {
		m = (log_2*(i+ j_0)) % (sizeOfField);
		S[i] = v.reduce(field->getGF(m + 1), field);
		//S[i] = v.reduce(power(primitive, i+ j_0, field), field);
	}

	//BM algorithm 
	
	int r = 0;
	int L = 0;
	while (r != 2 * t) {
		r++;
		for (int j = 0; j <= L; j++) {
			if ((field->getLog(S.get(r - j - 1)) == -1) || (field->getLog(lambda.get(j)) == -1))
			{
				mult_var = 0;
			}
			else
			{
				m = ((field->getLog(lambda.get(j))) + (field->getLog(S.get(r - j - 1)))) % sizeOfField;
				mult_var = field->getGF(m + 1);
				delta = (j == 0) ? mult_var : delta^mult_var;
			}
		}
		if (delta != 0) {
			int  delta_log = field->getLog(delta);
			temp.resize(B.getSize()+1);
			for (int i = 0; i < B.getSize(); i++) {
				if (B[i] == 0)
					temp[i+1] = 0;
				else
				{
					int m = (delta_log + (field->getLog(B[i]))) % (sizeOfField);
					temp[i+1] = field->getGF(m + 1);
				}
			}
			//deltax[1] = delta;
			//temp = deltax*B;
			T = lambda + temp;
			if (2 * L <= r - 1) {
				int log_deltarev;
				if (delta == 1)
					log_deltarev = field->getLog(1);
				else
					log_deltarev = field->getLog(field->getGF((1 << field->getPower()) - delta_log));
				B.resize(lambda.getSize());
				for (int i = 0; i < lambda.getSize(); i++) {
					if (lambda[i] == 0)
						B[i] = 0;
					else
					{	
						int m = (log_deltarev + (field->getLog(lambda[i]))) % (sizeOfField);
						B[i] = field->getGF(m + 1);
					}
				}
				lambda = T;
				L = r - L;
			}
			else {
				lambda = T;
				B *= X;
			}
		}
		else {
			B *= X;
		}
	}
	if (lambda.deg() != L) {
		cout << "too much mistakes!";
	}

	//Positions of errors

	posit.resize(2 * t);
	for (int i = 0; i < (sizeOfField); i++) {
		 m = (log_2*i) % (sizeOfField);
		power_var = field->getGF(m + 1);
		reduce_var = lambda.reduce(power_var, field);
		if (reduce_var == 0) {
			posit[counter] = power_var;
			counter++;
			continue;
		}
	}
	posit.resize(counter);
	GF_Vector omega(field);
	omega = S*lambda;		
	omega.resize(2 * t);
	GF_Vector lambda2(field, counter);
	GF_Vector error(field, v.getSize());
	int temp4 = 0;
	for (int i = 0; i < counter; i++) {
		if (i % 2 == 0)
			lambda2[i] = lambda[i + 1];
	}
	int index;
	for (int i = 0; i < counter; i++) {
		/*if (posit[i] == 1)
			index = field->getLog(1);
		else
			index = field->getLog(field->getGF((1 << field->getPower()) - field->getLog(posit[i])));
		rev_var = field->getGF((sizeOfField + 1) - field->getLog(lambda2.reduce(posit[i], field)));
		reduce_var = omega.reduce(posit[i], field);
		if ((rev_var == 0) || (reduce_var == 0)) {
			error[index] = 0;
		}
		else
		{	m = ((field->getLog(reduce_var)) + (field->getLog(rev_var))) % (sizeOfField);
			error[index] = field->getGF(m + 1);}*/

			/*index = field->getLog(field->getGF((1 << field->getPower()) - field->getLog(posit[i])));*/


		// some strange stuff

		index = field->getLog(rev(posit[i], field));
		/*rev_var = field->getGF((1 << field->getPower()) - field->getLog(lambda2.reduce(posit[i], field)));
		reduce_var = omega.reduce(posit[i], field);
		if ((field->getLog(rev_var) == -1) || (field->getLog(reduce_var) == -1))
		{return 0;}
		else
		{	m = ((field->getLog(reduce_var)) + (field->getLog(rev_var))) % (sizeOfField);
		mult_var = field->getGF(m + 1);}
		error[index] = mult_var;
		*/
		temp4 = mult(omega.reduce(posit[i], field),
			rev(lambda2.reduce(posit[i], field), field), field);
		error[index] = temp4;
		error[index] = mult(temp4, rev(power(2, j_0 - 1, field), field), field);
	}


	
	GF_Vector inf(field);
	inf = v + (error);
	cout << "what we wanted to say:" << endl;
	cout << inf;
}


