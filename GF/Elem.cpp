//#pragma once
//#include "Elem.h"
//#include "GF.h"
//Elem::Elem()
//{
//}
//
//Elem::Elem(int p, GF* g)
//{
//	polynom=p;
//	galua=g;
//}
//
//Elem::Elem(const Elem& element)
//{
//	polynom = element.polynom;
//	galua = element.galua;
//}
//
//Elem Elem:: operator +(const Elem& element)
//{
//	Elem sum(polynom^element.polynom, element.galua);
//	return sum;
//
//}
//
//Elem Elem::operator+= (const Elem& element){
//	Elem sum(polynom^element.polynom, element.galua);
//	return sum;
//}
//
//Elem Elem::operator = (const Elem& snd){
//	polynom = snd.polynom;
//	galua = snd.galua;
//	return *this;
//}
//
//GF* Elem:: get_gf(){
//	return galua;
//}
//
//const int Elem::getPoly() const{
//	return polynom;
//}
//
//Elem Elem::operator *(const Elem& element)
//{
//	if ((galua->Log_Table[element.polynom]==-1)|| (galua->Log_Table[polynom]==-1))
//	{Elem mult(0, galua);
//	return mult;
//	}
//	else
//	{int m = ((galua->Log_Table[polynom])+(galua->Log_Table[element.polynom]))%((1<<galua->power)-1);
//	Elem mult(galua->GF_Table[m+1], galua);
//	return mult;}
//}
//
//Elem Elem::operator *(const int element){
//	Elem elem(element, galua);
//	return *this*elem;
//}
//
//Elem Elem::operator/ (const Elem& element)
//{
//	return *this*element.rev();
//	//int d;
//	////if ((galua->Log_Table[polynom])<(galua->Log_Table[element.polynom]))
//	////{
//	////	Elem div(0, galua);
//	////	return div;
//	////}
//	///*else */if(galua->Log_Table[polynom]==0)
//	//{
//	//	Elem div(0, galua);
//	//	return div;
//	//}
//	//else
//	//{
//	//	d= ((galua->Log_Table[polynom])-(galua->Log_Table[element.polynom])) % ((1 << galua->power) - 1);
//	//	Elem div(galua->GF_Table[d + 1], galua);
//	//	return div;
//	//}
//}
//
//Elem Elem::operator^ (int a){
//	int m = ((galua->Log_Table[polynom])*a)%((1 << galua->power) - 1); 
//	Elem deg(galua->GF_Table[m + 1], galua);
//	return deg; 
//}
//
//int deg(int *GF_Table, int *Log_Table, int polynom, int deg, int n){
//	int m = ((Log_Table[polynom])*deg)%(n-1); 
//	return GF_Table[m+1];
//}
//
//bool Elem::isZero(){
//	return (this->polynom == 0);
//}
//
//Elem Elem::rev(){
//	if(this->polynom == 1)
//		return *this;
//	Elem rev (galua->GF_Table[(1 << galua->power)-galua->Log_Table[polynom]], galua);
//	return rev;
//}
//
//Elem Elem::rev() const {
//	if(this->polynom == 1)
//		return *this;
//	Elem rev (galua->GF_Table[(1 << galua->power)-galua->Log_Table[polynom]], galua);
//	return rev;
//}