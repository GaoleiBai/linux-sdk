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
   
   
#include "nlong.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdio.h>
#include <typeinfo>

NLong::NLong()
{
	value = 0;
}

NLong::NLong(long n)
{
	value = n;
}

NLong::~NLong()
{
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
	
	long long ll = atoll(cadena);
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
	if (typeid(*this) == typeid(o)) {
		long vo = ((NLong *)&o)->value;
		if (value > vo) return 1;
		else if (value < vo) return -1;
		else return 0;
	}
		
	return NObject::Compare(o);
}

void NLong::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NLong::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetLong();
}