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
#include "nulong.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <typeinfo>

NULong::NULong()
{
	value = 0;
}

NULong::NULong(unsigned long n)
{
	value = n;
}

NULong::NULong(const NULong &n)
{
	value = n.value;
}

NULong::~NULong()
{
}

NULong &NULong::operator =(const NULong &n)
{
	value = n.value;
	return *this;
}

unsigned long NULong::MaxValue()
{
	return ULONG_MAX;
}

unsigned long NULong::MinValue()
{
	return 0;
}

unsigned long NULong::Parse(const Text &text)
{
	unsigned long n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NULong::TryParse(const Text &text, unsigned long &n)
{
	if (((Text *)&text)->StartsWith("-")) return false;
	char tt[1001];
	((Text *)&text)->GetAnsiString(tt, 1000);
	
	errno = 0;
	unsigned long long ull = strtoull(tt, NULL, 10);
	if (errno != 0) return false;
	if (ull < MinValue() || ull > MaxValue()) return false;
	n = ull;
	return true;
}

Text NULong::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

unsigned long &NULong::Value()
{
	return value;
}

NObject *NULong::NewInstance()
{
	return new NULong();
}

Text NULong::ToText()
{
	char tt[1001];
	sprintf(tt, "%lu", value);
	return (Text)tt;
}

int NULong::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NULong &)o);
}

int NULong::Compare(const NULong &l)
{
	if (value > l.value) return 1;
	else if (value < l.value) return -1;
	else return 0;
}

bool NULong::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NULong &)o).Value();
}

void NULong::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NULong::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetULong();
}

int NULong::COMPARER(const void *u, const void *v)
{
	unsigned long *uu = (unsigned long *)u;
	unsigned long *vv = (unsigned long *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}