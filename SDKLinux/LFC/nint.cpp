/* 
* LFC Library - Linux toolkit
* 
* Copyright (C) 2012, 2013 Daniel Mosquera Villanueva 
* (milkatoffeecuco@gmail.com)
* This file is part of LFC Library.
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*
**/
#include "nint.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <errno.h>

NInt::NInt()
{
	value = 0;
}

NInt::NInt(const NInt &i)
{
	value = i.value;
}

NInt::NInt(int n)
{
	value = n;
}

NInt::~NInt()
{
}

NInt &NInt::operator =(const NInt &n)
{
	value = n.value;
	return *this;
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
	
	errno = 0;
	long long ll = atol(cadena);
	if (errno != 0) return false;
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
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NInt &)o);
}

int NInt::Compare(const NInt &i)
{
	if (value > i.value) return 1;
	else if (value < i.value) return -1;
	else return 0;
}

bool NInt::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NInt &)o).Value();
}

void NInt::Serialize(const Serializator &s) 
{
	((Serializator *)&s)->Put(value);
}

void NInt::Deserialize(const Serializator &s) 
{
	value = ((Serializator *)&s)->GetInt();
}

int NInt::COMPARER(const void *u, const void *v)
{
	int *uu = (int *)u;
	int *vv = (int *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	return 0;
}
