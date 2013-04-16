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
#include "nlong.h"
#include "Text/text.h"
#include "Devices/stdout.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdio.h>
#include <typeinfo>
#include <errno.h>

NLong::NLong()
{
	value = 0;
}

NLong::NLong(const NLong &l)
{
	value = l.value;
}

NLong::NLong(long n)
{
	value = n;
}

NLong::~NLong()
{
}

NLong &NLong::operator =(const NLong &n)
{
	value = n.value;
	return *this;
}

long NLong::MaxValue()
{
	return LONG_MAX;
}

long NLong::MinValue()
{
	return LONG_MIN;
}

long NLong::Parse(const Text &text)
{
	long l = 0;
	if (!TryParse(text, l))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return l;
}

bool NLong::TryParse(const Text &text, long &n)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	
	errno = 0;
	long long ll = atoll(cadena);
	if (errno != 0) return false;
	if (ll > MaxValue() || ll < MinValue()) return false;
	n = ll;
	return true;
}

Text NLong::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

long &NLong::Value()
{
	return value;
}

NObject *NLong::NewInstance()
{
	return new NLong();
}

Text NLong::ToText()
{
	char cadena[1001];
	sprintf(cadena, "%ld", value);
	return (Text)cadena;
}

int NLong::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NLong &)o);
}

int NLong::Compare(const NLong &l)
{
	if (value > l.value) return 1;
	else if (value < l.value) return -1;
	else return 0;
}

bool NLong::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NLong &)o).Value();
}

void NLong::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NLong::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetLong();
}

int NLong::COMPARER(const void *u, const void *v)
{
	long *uu = (long *)u;
	long *vv = (long *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}