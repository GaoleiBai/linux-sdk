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
   
   
#include "nuint.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdio.h>
#include <limits.h>
#include <typeinfo>
#include <errno.h>

NUInt::NUInt()
{
	value = 0;
}

NUInt::NUInt(unsigned int n)
{
	value = n;
}

NUInt::NUInt(const NUInt &n)
{
	value = n.value;
}

NUInt::~NUInt()
{
}

unsigned int NUInt::MaxValue()
{
	return UINT_MAX;
}

unsigned int NUInt::MinValue()
{
	return 0;
}

unsigned int NUInt::Parse(const Text &text)
{
	unsigned int n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NUInt::TryParse(const Text &text, unsigned int &n)
{
	char tt[1001];
	((Text *)&text)->GetAnsiString(tt, 1000);
	
	long long ll = atoll(tt);
	if (errno != 0) return false;
	if (ll > MaxValue() || ll < MinValue()) return false;
	n = ll;
	return true;
}

Text NUInt::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

unsigned int &NUInt::Value()
{
	return value;
}

NObject *NUInt::NewInstance()
{
	return new NUInt();
}

Text NUInt::ToText()
{
	char cadena[1001];
	sprintf(cadena, "%u", value);
	return (Text)cadena;
}

int NUInt::Compare(const NObject &o)
{
	long long vo = ((NObject *)&o)->ToLongLong();
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;
}

void NUInt::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NUInt::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetUInt();
}

long long NUInt::ToLongLong()
{
	return value;
}

long double NUInt::ToLongDouble()
{
	return value;
}