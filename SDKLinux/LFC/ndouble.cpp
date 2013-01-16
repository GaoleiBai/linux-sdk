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
   
   
#include "ndouble.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

NDouble::NDouble()
{
	value = 0;
}

NDouble::NDouble(double n)
{
	value = n;
}

NDouble::~NDouble()
{
}

double NDouble::Epsilon()
{
	return DBL_EPSILON;
}

double NDouble::NaN()
{
	return NAN;
}

double NDouble::PositiveInfinity()
{
	return INFINITY;
}

double NDouble::NegativeInfinity()
{
	return -INFINITY;
}

double NDouble::MaxValue()
{
	return DBL_MAX;
}

double NDouble::MinValue()
{
	return DBL_MIN;
}

double NDouble::Parse(const Text& text)
{
	double n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NDouble::TryParse(const Text &text, double &n)
{
	char tt[1001];
	((Text *)&text)->GetAnsiString(tt, 1000);
	
	long double ll = strtod(tt, NULL);
	if (ll > MaxValue() || ll < MinValue()) return false;
	n = ll;
	return true;
}

Text NDouble::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

double &NDouble::Value()
{
	return value;
}

bool NDouble::IsNaN(double f)
{
	return isnan(f);
}

bool NDouble::IsInfinity(double f)
{
	return isinf(f);
}

bool NDouble::IsFinite(double f)
{
	return isfinite(f);
}

NObject *NDouble::NewInstance()
{
	return new NDouble();
}

Text NDouble::ToText()
{
	char tt[1001];
	sprintf(tt, "%f", value);
	return (Text)tt;
}

int NDouble::Compare(const NObject &o)
{
	long double vo = ((NObject *)&o)->ToLongDouble();
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;
}

void NDouble::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NDouble::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetDouble();
}

long long NDouble::ToLongLong()
{
	return value;
}

long double NDouble::ToLongDouble()
{
	return value;
}