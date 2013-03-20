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
#ifndef NCHAR_H
#define NCHAR_H

#include "n_object.h"

class Text;

class NChar : public NObject {

public:
	NChar();
	NChar(char c);
	NChar(const NChar &c);
	virtual ~NChar();

	static char MaxValue();
	static char MinValue();
	static char Parse(const Text &text);
	static bool TryParse(const Text &text, char &c);
	Text ToText(const Text &format);
	
	char &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual int Compare(const NChar &c);
	virtual bool Equals(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	static int COMPARER(const void *u, const void *v);
	
	bool IsAlpha(char c);
	bool IsAlphaNumeric(char c);
	bool IsAscii(char c);
	bool IsBlank(char c);
	bool IsControl(char c);
	bool IsDigit(char c);
	bool IsGraph(char c);
	bool IsLower(char c);
	bool IsPrintable(char c);
	bool IsPunctuation(char c);
	bool IsSpace(char c);
	bool IsUpper(char c);
	bool IsXDigit(char c);

protected:
	char value;
	
};

#endif // NCHAR_H
