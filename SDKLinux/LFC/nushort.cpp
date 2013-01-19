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
   
   
#include "nushort.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <typeinfo>
#include <errno.h>

NUShort::NUShort()
{
	value = 0;
}

NUShort::NUShort(unsigned short n)
{
	value = n;
}

NUShort::NUShort(const NUShort &n)
{
	value = n.value;
}

NUShort::~NUShort()
{
}

unsigned short NUShort::MinValue()
{
	return 0;
}

unsigned short NUShort::MaxValue()
{
	return USHRT_MAX;
}

unsigned short NUShort::Parse(const Text &text)
{
	unsigned short n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NUShort::TryParse(const Text &text, unsigned short &n)
{
	char tt[1001];
	((Text *)&text)->GetAnsiString(tt, 1000);
	
	long long ll = atoll(tt);
	if (errno != 0) return false;
	if (ll < MinValue() || ll > MaxValue()) return false;
	n = ll;
	return true;
}

Text NUShort::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

unsigned short &NUShort::Value()
{
	return value;
}

NObject *NUShort::NewInstance()
{
	return new NUShort();
}

Text NUShort::ToText()
{
	char tt[1001];
	sprintf(tt, "%hu", value);
	return (Text)tt;
}

int NUShort::Compare(const NObject &o)
{
	long long vo = ((NObject *)&o)->ToLongLong();
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;
}

void NUShort::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NUShort::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetUShort();
}

long long NUShort::ToLongLong()
{
	return value;
}

long double NUShort::ToLongDouble()
{
	return value;
}