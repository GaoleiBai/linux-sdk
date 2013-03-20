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
#include "nulonglong.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <typeinfo>

NULongLong::NULongLong()
{
	value = 0;
}

NULongLong::NULongLong(unsigned long long n)
{
	value = n;
}

NULongLong::NULongLong(const NULongLong &n)
{
	value = n.value;
}

NULongLong::~NULongLong()
{
}

unsigned long long NULongLong::MaxValue()
{
	return ULLONG_MAX;
}

unsigned long long NULongLong::MinValue()
{
	return 0;
}

unsigned long long NULongLong::Parse(const Text &text)
{
	unsigned long long n = 0;
	if (!TryParse(text, n))
		throw new Exception(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return n;
}

bool NULongLong::TryParse(const Text &text, unsigned long long &n)
{
	if (((Text *)&text)->StartsWith("-")) return false;
	char tt[1001];
	((Text *)&text)->GetAnsiString(tt, 1000);
	
	errno = 0;
	unsigned long long ll = strtoull(tt, NULL, 10);
	if (errno != 0) return false;
	n = ll;
	return true;
}

Text NULongLong::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, 1000);
	return (Text)tt;
}

unsigned long long &NULongLong::Value()
{
	return value;
}

NObject *NULongLong::NewInstance()
{
	return new NULongLong();
}

Text NULongLong::ToText()
{
	char tt[1001];
	sprintf(tt, "%llu", value);
	return (Text)tt;
}

int NULongLong::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NULongLong &)o);
}

int NULongLong::Compare(const NULongLong &l)
{
	if (value > l.value) return 1;
	else if (value < l.value) return -1;
	else return 0;
}

bool NULongLong::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NULongLong &)o).Value();
}

void NULongLong::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NULongLong::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetULongLong();
}

int NULongLong::COMPARER(const void *u, const void *v)
{
	unsigned long long *uu = (unsigned long long *)u;
	unsigned long long *vv = (unsigned long long *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}