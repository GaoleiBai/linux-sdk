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
#ifndef NFLOAT_H
#define NFLOAT_H

#include "n_object.h"

class Text;

class NFloat : public NObject {

public:
	NFloat();
	NFloat(float n);
	NFloat(const NFloat &f);
	virtual ~NFloat();

	static float Epsilon();
	static float NaN();
	static float PositiveInfinity();
	static float NegativeInfinity();
	static float MaxValue();
	static float MinValue();
	static float Parse(const Text &text);
	static bool TryParse(const Text &text, float &n);
	Text ToText(const Text &format);
	
	float &Value();
	static bool IsNaN(float f);
	static bool IsInfinity(float f);
	static bool IsFinite(float f);
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual int Compare(const NFloat &f);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	virtual long long ToLongLong();
	virtual long double ToLongDouble();
	
	static int COMPARER(const void *u, const void *v);
	
protected:
	float value;
	
};

#endif // NFLOAT_H
