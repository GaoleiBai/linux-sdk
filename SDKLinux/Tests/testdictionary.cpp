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
   
   
#include "../LFC/LFC.h"
#include "testdictionary.h"

TestDictionary::TestDictionary()
{
}

TestDictionary::~TestDictionary()
{
}

int TestDictionary::Perform()
{
	Dictionary<Text *, int> d1(Text::COMPARER);
	d1.SetKey(new Text("Luis"), 10);
	d1.SetKey(new Text("Pedro"), 4);
	d1.SetKey(new Text("Alvaro"), 20);
	d1.SetKey(new Text("Luis"), 12);
	d1.SetKey(new Text("Zacarias"), 23);
	d1.SetKey(new Text("Armando"), 15);
	
	int iAux = 0;
	Collection<Text *> keys = d1.Keys();
	Collection<int> values = d1.Values();
	for (int i=0; i<keys.Count(); i++) {
		if (!d1.GetKey(keys[i], iAux)) {
			StdOut::PrintLine("Dictionary<K, V>::GetKey didn't work!!!");
			return -1;
		}
		if (iAux != values[i]) {
			StdOut::PrintLine("Dictionary<K, V>::Values didn't work!!!");
			return -1;
		}
		StdOut::PrintLine(*keys[i] + " " + iAux);
	}
	
	Text t = "Luis";
	d1.ClearKey(&t);
	if (d1.ExistsKey(&t)) {
		StdOut::PrintLine("ClearKey and ExistsKey doesn't work!!!");
		return -1;
	}
	
	NObjectDictionary d2;
	d2.SetKey(new Text("Octubre"), new Text("Rojo"));
	d2.SetKey(new Text("Manolo"), new Text("Machado"));
	d2.SetKey(new Text("Carmen"), new Text("Chacon"));
	d2.SetKey(new Text("Felipe"), new Text("González"));
	NObject *oaux = NULL;
	Collection<NObject *> d2keys = d2.Keys();
	for (int i=0; i<d2keys.Count(); i++) {
		if (d2.GetKey(d2keys[i], oaux)) continue;
		StdOut::PrintLine("NObjectDictionary error!!!");
		return -1;
	}
	StdOut::PrintLine(d2.ToText());
	d2.DeleteAndClear();
	
	try { 
		d2.SetKey(NULL, new Text("aaa")); 
		StdOut::PrintLine("Exception should have been raised.");
		return -1;
	} catch (Exception *e) {
		delete e;
	}
	
	try { 
		d2.SetKey(new Text("aaa"), NULL); 
		StdOut::PrintLine("Exception should have been raised.");
		return -1;
	} catch (Exception *e) {
		delete e;
	}
	
	return 0;
}

