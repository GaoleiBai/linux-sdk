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
   
   
#include "nuchar.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdio.h>
#include <limits.h>
#include <typeinfo>

NUChar::NUChar()
{
	value = 0;
}

NUChar::NUChar(unsigned char n)
{
	value = n;
}

NUChar::NUChar(const NUChar &n)
{
	value = n.value;
}

NUChar::~NUChar()
{
}

unsigned char NUChar::MaxValue()
{
	UCHAR_MAX;
}

unsigned char NUChar::MinValue()
{
	return 0;
}

unsigned char NUChar::Parse(const Text &text)
{
	unsigned char n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NUChar::TryParse(const Text &text, unsigned char &c)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	
	long long ll = atoll(cadena);
	if (ll > MaxValue() || ll < MinValue()) return false;
	c = ll;
	return true;
}

Text NUChar::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

unsigned char &NUChar::Value()
{
	return value;
}

NObject *NUChar::NewInstance()
{
	return new NUChar();
}

Text NUChar::ToText()
{
	char tt[1001];
	sprintf(tt, "%hhu", value);
	return (Text)tt;
}

int NUChar::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o))
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	
	unsigned char vo = ((NUChar *)&o)->value;
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;
}

void NUChar::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NUChar::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetUChar();
}

long long NUChar::ToLongLong()
{
	return value;
}

long double NUChar::ToLongDouble()
{
	return value;
}