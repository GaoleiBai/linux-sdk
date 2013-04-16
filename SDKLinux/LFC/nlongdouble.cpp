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
#include <typeinfo>

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

NLongDouble &NLongDouble::operator =(const NLongDouble &n)
{
	value = n.value;
	return *this;
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
	return -LDBL_MAX;
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
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NLongDouble &)o);
}

int NLongDouble::Compare(const NLongDouble &d)
{
	if (value > d.value) return 1;
	else if (value < d.value) return -1;
	else return 0;
}

bool NLongDouble::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NLongDouble &)o).Value();
}

void NLongDouble::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NLongDouble::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetLongDouble();
}

int NLongDouble::COMPARER(const void *u, const void *v)
{
	long double *uu = (long double *)u;
	long double *vv = (long double *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}