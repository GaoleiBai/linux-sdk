/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva (daniel.m.v@terra.es)
   This file is part of LFC Library.

   LFC Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   LFC Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with LFC Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA. or see http://www.gnu.org/licenses/. */
   
   
#include "testcollection.h"
#include "../LFC/LFC.h"

TestCollection::TestCollection()
{
}

TestCollection::~TestCollection()
{
}

int TestCollection::Perform()
{
	Collection<Text *> c1;
	c1.Add(new Text("Cóngrio"));
	c1.Add(new Text("Balón"));
	c1.Add(new Text("Escoba"));
	c1.Add(new Text("Pala"));
	c1.Add(new Text("General"));
	c1.Add(new Text("Camino"));
	c1.Add(new Text("Cáñamo"));
	c1.Add(new Text("Barrotes"));
	c1.Add(new Text("Sol"));
	c1.Add(new Text("Luna"));
	c1.Add(new Text("Tierra"));
	c1.Add(new Text("Balon"));
	c1.Add(new Text("Canalización"));
	c1.Add(new Text("Camarilla"));
	c1.Add(new Text("Cooperación"));
	c1.QuickSort(Text::COMPARER);
	for (int i=0; i<c1.Count(); i++) StdOut::PrintLine(*c1[i]);
	for (int i=1; i<c1.Count(); i++) {
		if (*c1[i-1] > *c1[i]) {
			StdOut::PrintLine("Collection<T>::Sort didn't work!!!");
			return -1;
		}
	}
	
	Text ttierra = "Tierra";
	int ixTierra = c1.BinarySearchIx(&ttierra, Text::COMPARER);
	if (ixTierra != 14) {
		StdOut::PrintLine("Collection<T>::BinarySearchIx didn't work!!!");
		return -1;
	}
	
	Text tpetardo = "Petardo";
	int ixpetardo = c1.BinarySearchIx(&tpetardo, Text::COMPARER);
	if (ixpetardo != -1) {
		StdOut::PrintLine("Collection<T>::BinarySearchIx didn't work!!!");
		return -1;
	}
	
	c1.InsertAt(0, new Text("Primero"));
	c1.InsertAt(c1.Count(), new Text("Ultimo"));
	if ((Text)"Primero" != c1.First() ||
		(Text)"Ultimo" != c1.Last()) 
	{
		StdOut::PrintLine("Collection<T>::InsertAt didn't work!!!");
		return -1;
	}
	
	for (int i=0; i<c1.Count(); i++)
		StdOut::PrintLine(*c1[i]);
	c1.DeleteAndClear();
	if (c1.Count() != 0) {
		StdOut::PrintLine("Collection<T>::DeleteAndClear didn't work!!!");
		return -1;
	}
	
	Collection<DateTime *> c2;
	c2.Add(new DateTime(1977, 6, 3));
	c2.Add(new DateTime(1981, 3, 1));
	c2.Add(new DateTime(1976, 7, 9));
	c2.Add(new DateTime(1975, 8, 21));
	c2.Add(new DateTime(1974, 11, 14));
	c2.QuickSort(DateTime::COMPARER);
	for (int i=0; i<c2.Count(); i++)
		StdOut::PrintLine(c2[i]->ToText());
		
	if (c2.Count() != 5) {
		StdOut::PrintLine("Collection<T>::Add didn't work!!!");
		return -1;
	}
	
	c2.DeleteAndClear();
	if (c2.Count() != 0) {
		StdOut::PrintLine("Collection<T>::DeleteAndClear didn't work!!!");
		return -1;
	}
	
	Collection<int> c3;
	c3.Add(1);
	c3.Clear();
	
	NObjectCollection noc;
	noc.Add(new Text("aaa"));
	noc.Add(new DateTime());
	for (int i=0; i<noc.Count(); i++)
		StdOut::PrintLine(noc[i]->ToText());
	noc.DeleteAndClear();
	
	Collection<bool> cb;
	cb.Add(true);
	cb.Add(false);
	cb.Add(true);
	cb.Add(false);
	cb.Add(true);
	cb.Add(false);
	cb.Add(true);
	cb.Add(false);
	cb.QuickSort(NChar::COMPARER);
	for (int i=1; i<cb.Count(); i++) {
		if (cb[i-1] && !cb[i]) {
			StdOut::PrintLine("Collection<bool> error");
			return -1;
		}
	}
	
	Collection<char> cchar;
	cchar.Add('9');
	cchar.Add('1');
	cchar.Add('8');
	cchar.Add('2');
	cchar.Add('7');
	cchar.Add('3');
	cchar.Add('6');
	cchar.Add('4');
	cchar.QuickSort(NChar::COMPARER);
	for (int i=1;i<cchar.Count(); i++) {
		if (cchar[i-1] < cchar[i]) continue;
		StdOut::PrintLine("Collection<char> error");
		return -1;
	}
	
	Collection<short> cshort;
	cshort.Add(9);
	cshort.Add(1);
	cshort.Add(8);
	cshort.Add(2);
	cshort.Add(7);
	cshort.Add(3);
	cshort.Add(6);
	cshort.Add(4);
	cshort.QuickSort(NShort::COMPARER);
	for (int i=1;i<cshort.Count(); i++) {
		if (cshort[i-1] < cshort[i]) continue;
		StdOut::PrintLine("Collection<short> error");
		return -1;
	}
	
	Collection<int> cint;
	cint.Add(9);
	cint.Add(1);
	cint.Add(8);
	cint.Add(2);
	cint.Add(7);
	cint.Add(3);
	cint.Add(6);
	cint.Add(4);
	cint.QuickSort(NInt::COMPARER);
	for (int i=1;i<cint.Count(); i++) {
		if (cint[i-1] < cint[i]) continue;
		StdOut::PrintLine("Collection<int> error");
		return -1;
	}
	
	Collection<long> clong;
	clong.Add(9);
	clong.Add(1);
	clong.Add(8);
	clong.Add(2);
	clong.Add(7);
	clong.Add(3);
	clong.Add(6);
	clong.Add(4);
	clong.QuickSort(NLong::COMPARER);
	for (int i=1;i<clong.Count(); i++) {
		if (clong[i-1] < clong[i]) continue;
		StdOut::PrintLine("Collection<long> error");
		return -1;
	}
	
	Collection<long long> clonglong;
	clonglong.Add(9);
	clonglong.Add(1);
	clonglong.Add(8);
	clonglong.Add(2);
	clonglong.Add(7);
	clonglong.Add(3);
	clonglong.Add(6);
	clonglong.Add(4);
	clonglong.QuickSort(NLongLong::COMPARER);
	for (int i=1;i<clonglong.Count(); i++) {
		if (clonglong[i-1] < clonglong[i]) continue;
		StdOut::PrintLine("Collection<long long> error");
		return -1;
	}
	
	Collection<unsigned char> cuchar;
	cuchar.Add('9');
	cuchar.Add('1');
	cuchar.Add('8');
	cuchar.Add('2');
	cuchar.Add('7');
	cuchar.Add('3');
	cuchar.Add('6');
	cuchar.Add('4');
	cuchar.QuickSort(NUChar::COMPARER);
	for (int i=1;i<cuchar.Count(); i++) {
		if (cuchar[i-1] < cuchar[i]) continue;
		StdOut::PrintLine("Collection<unsigned char> error");
		return -1;
	}
	
	Collection<unsigned short> cushort;
	cushort.Add(9);
	cushort.Add(1);
	cushort.Add(8);
	cushort.Add(2);
	cushort.Add(7);
	cushort.Add(3);
	cushort.Add(6);
	cushort.Add(4);
	cushort.QuickSort(NUShort::COMPARER);
	for (int i=1;i<cushort.Count(); i++) {
		if (cushort[i-1] < cushort[i]) continue;
		StdOut::PrintLine("Collection<unsigned short> error");
		return -1;
	}
	
	Collection<unsigned int> cuint;
	cuint.Add(9);
	cuint.Add(1);
	cuint.Add(8);
	cuint.Add(2);
	cuint.Add(7);
	cuint.Add(3);
	cuint.Add(6);
	cuint.Add(4);
	cuint.QuickSort(NUInt::COMPARER);
	for (int i=1;i<cuint.Count(); i++) {
		if (cuint[i-1] < cuint[i]) continue;
		StdOut::PrintLine("Collection<unsigned int> error");
		return -1;
	}
	
	Collection<unsigned long> culong;
	culong.Add(9);
	culong.Add(1);
	culong.Add(8);
	culong.Add(2);
	culong.Add(7);
	culong.Add(3);
	culong.Add(6);
	culong.Add(4);
	culong.QuickSort(NULong::COMPARER);
	for (int i=1;i<culong.Count(); i++) {
		if (culong[i-1] < culong[i]) continue;
		StdOut::PrintLine("Collection<unsigned long> error");
		return -1;
	}
	
	Collection<unsigned long long> culonglong;
	culonglong.Add(9);
	culonglong.Add(1);
	culonglong.Add(8);
	culonglong.Add(2);
	culonglong.Add(7);
	culonglong.Add(3);
	culonglong.Add(6);
	culonglong.Add(4);
	culonglong.QuickSort(NULongLong::COMPARER);
	for (int i=1;i<culonglong.Count(); i++) {
		if (culonglong[i-1] < culonglong[i]) continue;
		StdOut::PrintLine("Collection<unsigned long long> error");
		return -1;
	}
	
	Collection<float> cfloat;
	cfloat.Add(9);
	cfloat.Add(1);
	cfloat.Add(8);
	cfloat.Add(2);
	cfloat.Add(7);
	cfloat.Add(3);
	cfloat.Add(6);
	cfloat.Add(4);
	cfloat.QuickSort(NFloat::COMPARER);
	for (int i=1;i<cfloat.Count(); i++) {
		if (cfloat[i-1] < cfloat[i]) continue;
		StdOut::PrintLine("Collection<float> error");
		return -1;
	}
	
	Collection<double> cdouble;
	cdouble.Add(9);
	cdouble.Add(1);
	cdouble.Add(8);
	cdouble.Add(2);
	cdouble.Add(7);
	cdouble.Add(3);
	cdouble.Add(6);
	cdouble.Add(4);
	cdouble.QuickSort(NDouble::COMPARER);
	for (int i=1;i<cdouble.Count(); i++) {
		if (cdouble[i-1] < cdouble[i]) continue;
		StdOut::PrintLine("Collection<double> error");
		return -1;
	}
	
	Collection<long double> cldouble;
	cldouble.Add(9);
	cldouble.Add(1);
	cldouble.Add(8);
	cldouble.Add(2);
	cldouble.Add(7);
	cldouble.Add(3);
	cldouble.Add(6);
	cldouble.Add(4);
	cldouble.QuickSort(NLongDouble::COMPARER);
	for (int i=1;i<cldouble.Count(); i++) {
		if (cldouble[i-1] < cldouble[i]) continue;
		StdOut::PrintLine("Collection<long double> error");
		return -1;
	}
	
	return 0;
}
