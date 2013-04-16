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
#include "nlonglong.h"
#include "nlong.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdio.h>
#include <typeinfo>
#include <errno.h>

NLongLong::NLongLong()
{
	value = 0;
}

NLongLong::NLongLong(long long n)
{
	value = n;
}

NLongLong::NLongLong(const NLongLong &l)
{
	value = l.value;
}

NLongLong::~NLongLong()
{
}

NLongLong &NLongLong::operator =(const NLongLong &n)
{
	value = n.value;
	return *this;
}

long long NLongLong::MaxValue()
{
	return LLONG_MAX;
}

long long NLongLong::MinValue()
{
	return LLONG_MIN;
}

long long NLongLong::Parse(const Text &text)
{
	long long ll = 0;
	TryParse(text, ll);
	if (errno != 0) 
		throw new Exception(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return ll;
}

bool NLongLong::TryParse(const Text &text, long long &n)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	
	errno = 0;
	n = atoll(cadena);
	return errno == 0;
}

Text NLongLong::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(ff, tt, value);
	return (Text)tt;
}

long long &NLongLong::Value()
{
	return value;
}

NObject *NLongLong::NewInstance()
{
	return new NLongLong();
}

Text NLongLong::ToText()
{
	char cadena[1001];
	sprintf(cadena, "%lld", value);
	return (Text)cadena;
}

int NLongLong::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NLongLong &)o);
}

int NLongLong::Compare(const NLongLong &l)
{
	if (value > l.value) return 1;
	else if (value < l.value) return -1;
	else return 0;
}

bool NLongLong::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NLongLong &)o).Value();
}

void NLongLong::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NLongLong::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetLongLong();
}

int NLongLong::COMPARER(const void *u, const void *v)
{
	long long *uu = (long long *)u;
	long long *vv = (long long *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}