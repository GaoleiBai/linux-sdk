/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva
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
   
   
#include "nint.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>

NInt::NInt()
{
	value = 0;
}

NInt::NInt(int n)
{
	value = n;
}

NInt::~NInt()
{
}

int NInt::MaxValue()
{
	return INT_MAX;
}

int NInt::MinValue()
{
	return INT_MIN;
}

int &NInt::Value()
{
	return value;
}

int NInt::Parse(const Text &text)
{
	int n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NInt::TryParse(const Text &text, int &n)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	
	long long ll = atoll(cadena);
	if (ll > MaxValue() || ll < MinValue()) return false;
	n = ll;
	return true;
}

Text NInt::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

NObject *NInt::NewInstance()
{
	return new NInt();
}

Text NInt::ToText()
{
	char cadena[1001];
	sprintf(cadena, "%d", value);
	return (Text)cadena;
}

int NInt::Compare(const NObject &o)
{
	long long vo = ((NObject *)&o)->ToLongLong();		
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;	
}

void NInt::Serialize(const Serializator &s) 
{
	((Serializator *)&s)->Put(value);
}

void NInt::Deserialize(const Serializator &s) 
{
	value = ((Serializator *)&s)->GetInt();
}

long long NInt::ToLongLong()
{
	return value;
}

long double NInt::ToLongDouble()
{
	return value;
}

