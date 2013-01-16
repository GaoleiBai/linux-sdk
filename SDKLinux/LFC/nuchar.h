/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva
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
   
   
#ifndef NUCHAR_H
#define NUCHAR_H

#include "n_object.h"

class Text;

class NUChar : public NObject {

public:
	NUChar();
	NUChar(unsigned char n);
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
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	virtual long long ToLongLong();
	virtual long double ToLongDouble();
	
protected:
	unsigned char value;
	
};

#endif // NUCHAR_H
