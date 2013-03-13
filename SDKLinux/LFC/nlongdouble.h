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
#ifndef NLONGDOUBLE_H
#define NLONGDOUBLE_H

#include "n_object.h"

class Text;

class NLongDouble : public NObject {

public:
	NLongDouble();
	NLongDouble(long double n);
	NLongDouble(const NLongDouble &l);
	virtual ~NLongDouble();

	static long double Epsilon();
	static long double NaN();
	static long double PositiveInfinity();
	static long double NegativeInfinity();
	static long double MaxValue();
	static long double MinValue();
	static long double Parse(const Text &text);
	static bool TryParse(const Text &text, long double &n);
	Text ToText(const Text &format);
	
	long double &Value();
	static bool IsNaN(long double f);
	static bool IsInfinity(long double f);
	static bool IsFinite(long double f);
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual int Compare(const NLongDouble &d);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	virtual long long ToLongLong();
	virtual long double ToLongDouble();
	
	static int COMPARER(const void *u, const void *v);

protected:
	long double value;
	
};

#endif // NLONGDOUBLE_H
