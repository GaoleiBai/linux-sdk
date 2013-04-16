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
#include "nshort.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdio.h>
#include <typeinfo>
#include <errno.h>

NShort::NShort()
{
	value = 0;
}

NShort::NShort(const NShort &s)
{
	value = s.value;
}

NShort::NShort(short s)
{
	value = s;
}

NShort::~NShort()
{
}

NShort &NShort::operator =(const NShort &e)
{
	value = e.value;
	return *this;
}

short NShort::MaxValue()
{
	return SHRT_MAX;
}

short NShort::MinValue()
{
	return SHRT_MIN;
}

short NShort::Parse(const Text &text)
{
	short s = 0;
	if (!TryParse(text, s))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return s;
}

bool NShort::TryParse(const Text &text, short &c)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	errno = 0;
	long long ll = atoll(cadena);
	if (errno != 0) return false;
	if (ll > MaxValue() || ll < MinValue()) return false;
	c = ll;
	return true;
}

Text NShort::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char ss[1001];
	sprintf(ss, ff, value);
	return (Text)ss;
}

short &NShort::Value()
{
	return value;
}

NObject *NShort::NewInstance()
{
	return new NShort();
}

Text NShort::ToText()
{
	char cadena[100];
	sprintf(cadena, "%hd", value);
	return (Text)cadena;
}

int NShort::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NShort &)o);
}

int NShort::Compare(const NShort &s)
{
	if (value > s.value) return 1;
	else if (value < s.value) return -1;
	else return 0;
}

bool NShort::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NShort &)o).Value();
}

void NShort::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NShort::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetShort();
}

int NShort::COMPARER(const void *u, const void *v)
{
	short *uu = (short *)u;
	short *vv = (short *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}