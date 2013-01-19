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
   
   
#include "nlongdouble.h"
#include "nlonglong.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <errno.h>

NLongDouble::NLongDouble()
{
	value = 0;
}

NLongDouble::NLongDouble(long double n)
{
	value = n;
}

NLongDouble::NLongDouble(const NLongDouble &l)
{
	value = l.value;
}

NLongDouble::~NLongDouble()
{
}

long double NLongDouble::Epsilon()
{
	return LDBL_EPSILON;
}

long double NLongDouble::NaN()
{
	return NAN;
}

long double NLongDouble::PositiveInfinity()
{
	return INFINITY;
}

long double NLongDouble::NegativeInfinity()
{
	return -INFINITY;
}

long double NLongDouble::MaxValue()
{
	return LDBL_MAX;
}

long double NLongDouble::MinValue()
{
	return LDBL_MIN;
}

long double NLongDouble::Parse(const Text &text)
{
	long double n = 0;
	if (!TryParse(text, n))
		throw new Exception(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return n;
}

bool NLongDouble::TryParse(const Text &text, long double &n)
{
	char tt[1001];
	((Text *)&text)->GetAnsiString(tt, 1000);
	
	errno = 0;
	long double ll = strtold(tt, NULL);
	if (errno != 0) return false;
	n = ll;
	return true;
}

Text NLongDouble::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return tt;
}

long double &NLongDouble::Value()
{
	return value;
}

bool NLongDouble::IsNaN(long double n)
{
	return isnan(n);
}

bool NLongDouble::IsInfinity(long double n)
{
	return isinf(n);
}

bool NLongDouble::IsFinite(long double n)
{
	return isfinite(n);
}

NObject *NLongDouble::NewInstance()
{
	return new NLongDouble();
}

Text NLongDouble::ToText()
{
	char tt[1001];
	sprintf(tt, "%Lf", value);
	return (Text)tt;
}

int NLongDouble::Compare(const NObject &o)
{
	long double vo = ((NObject *)&o)->ToLongDouble();
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;
}

void NLongDouble::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NLongDouble::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetLongDouble();
}

long long NLongDouble::ToLongLong()
{
	if (value > NLongLong::MaxValue() || value < NLongLong::MinValue())
		throw new Exception("Cannot convert to long long", __FILE__, __LINE__, __func__);
		
	return value;
}

long double NLongDouble::ToLongDouble()
{
	return value;
}