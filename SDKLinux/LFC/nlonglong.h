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
#ifndef NLONGLONG_H
#define NLONGLONG_H

#include "n_object.h"

class Text;

class NLongLong : public NObject {

public:
	NLongLong();
	NLongLong(long long n);
	NLongLong(const NLongLong &l);
	virtual ~NLongLong();
	
	virtual NLongLong &operator =(const NLongLong &n);

	static long long MaxValue();
	static long long MinValue();
	static long long Parse(const Text &text);
	static bool TryParse(const Text &text, long long &n);
	Text ToText(const Text &format);
	
	long long &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual int Compare(const NLongLong &l);
	virtual bool Equals(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	static int COMPARER(const void *u, const void *v);

protected:
	long long value;
	
};

#endif // NLONGLONG_H
