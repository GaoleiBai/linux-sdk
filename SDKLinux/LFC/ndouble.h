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
#ifndef NDOUBLE_H
#define NDOUBLE_H

#include "n_object.h"

class Text;

class NDouble : public NObject {

public:
	NDouble();
	NDouble(double n);
	NDouble(const NDouble &d);
	virtual ~NDouble();

	static double Epsilon();
	static double NaN();
	static double PositiveInfinity();
	static double NegativeInfinity();
	static double MaxValue();
	static double MinValue();
	static double Parse(const Text &text);
	static bool TryParse(const Text &text, double &n);
	Text ToText(const Text &format);
	
	double &Value();
	static bool IsNaN(double f);
	static bool IsInfinity(double f);
	static bool IsFinite(double f);
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual int Compare(const NDouble &d);
	virtual bool Equals(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	static int COMPARER(const void *u, const void *v);
	
protected:
	double value;
	
};

#endif // NDOUBLE_H
