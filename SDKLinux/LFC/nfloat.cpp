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
#include "nfloat.h"
#include "nlonglong.h"
#include "exception.h"
#include "Devices/stdout.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <errno.h>
#include <typeinfo>

NFloat::NFloat()
{
	value = 0;
}

NFloat::NFloat(float n)
{
	value = n;
}

NFloat::NFloat(const NFloat &f)
{
	value = f.value;
}

NFloat::~NFloat()
{
}

NFloat &NFloat::operator =(const NFloat &n)
{
	value = n.value;
	return *this;
}

float NFloat::Epsilon()
{
	return FLT_EPSILON;
}

float NFloat::NaN()
{
	return NAN;
}

float NFloat::PositiveInfinity()
{
	return INFINITY;
}

float NFloat::NegativeInfinity()
{
	return -INFINITY;
}

float NFloat::MaxValue()
{
	return FLT_MAX;
}

float NFloat::MinValue()
{
	return -FLT_MAX;
}

float NFloat::Parse(const Text &text)
{
	float n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NFloat::TryParse(const Text &text, float &n)
{
	char tt[1001];
	((Text *)&text)->GetAnsiString(tt, 1000);
	
	errno = 0;
	float ff = strtof(tt, NULL);
	if (errno != 0) return false;
	if (ff > MaxValue() || ff < MinValue()) return false;
	n = ff;
	return true;	
}

Text NFloat::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

float &NFloat::Value()
{
	return value;
}

bool NFloat::IsNaN(float f)
{
	return isnan(f);
}

bool NFloat::IsInfinity(float f)
{
	return isinf(f);
}

bool NFloat::IsFinite(float f)
{
	return isfinite(f);
}

NObject *NFloat::NewInstance()
{
	return new NFloat();
}

Text NFloat::ToText()
{
	char tt[1001];
	sprintf(tt, "%f", value);
	return (Text)tt;
}

int NFloat::Compare(const NObject &o)
{
	if (typeid(*this) != typeid(o)) 
		throw new Exception("Not comparable", __FILE__, __LINE__, __func__);
	return Compare((NFloat &)o);
}

int NFloat::Compare(const NFloat &f)
{
	if (value > f.value) return 1;
	else if (value < f.value) return -1;
	else return 0;
}

bool NFloat::Equals(const NObject &o)
{
	if (this == &o) return true;
	if (typeid(*this) != typeid(o)) return false;
	return Value() == ((NFloat &)o).Value();
}

void NFloat::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NFloat::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetFloat();
}

int NFloat::COMPARER(const void *u, const void *v)
{
	float *uu = (float *)u;
	float *vv = (float *)v;
	
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}