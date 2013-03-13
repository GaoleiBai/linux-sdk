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
#ifndef NUCHAR_H
#define NUCHAR_H

#include "n_object.h"

class Text;

class NUChar : public NObject {

public:
	NUChar();
	NUChar(unsigned char n);
	NUChar(const NUChar &u);
	virtual ~NUChar();

	static unsigned char MaxValue();
	static unsigned char MinValue();
	static unsigned char Parse(const Text &text);
	static bool TryParse(const Text &text, unsigned char &c);
	Text ToText(const Text &format);
	
	unsigned char &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual int Compare(const NUChar &c);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	virtual long long ToLongLong();
	virtual long double ToLongDouble();
	
	static int COMPARER(const void *u, const void *v);

protected:
	unsigned char value;
	
};

#endif // NUCHAR_H
