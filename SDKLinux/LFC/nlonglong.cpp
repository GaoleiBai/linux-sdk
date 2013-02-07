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
	long long vo = ((NObject *)&o)->ToLongLong();		
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;	
}

void NLongLong::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NLongLong::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetLongLong();
}

long long NLongLong::ToLongLong()
{
	if (value > NLong::MaxValue())
		throw new Exception("Cannot convert to long long", __FILE__, __LINE__, __func__);
	return value;
}

long double NLongLong::ToLongDouble()
{
	return value;
}

int NLongLong::COMPARER(const void *u, const void *v)
{
	long long *uu = (long long *)u;
	long long *vv = (long long *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}