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
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	virtual long long ToLongLong();
	virtual long double ToLongDouble();
	
	static int COMPARER(const void *u, const void *v);
	
	bool IsAlpha(char c);
	bool IsAlphaNumeric(char c);
	bool IsAscii(char c);
	bool IsControl(char c);
	bool IsDigit(char c);
	bool IsGraph(char c);
	bool IsLower(char c);
	bool IsPrintable(char c);
	bool IsPunctuation(char c);
	bool IsSpace(char c);
	bool IsUpper(char c);
	bool IsXDigit(char c);

	bool IsAlpha(wchar_t c);
	bool IsAlphaNumeric(wchar_t c);
	bool IsAscii(wchar_t c);
	bool IsControl(wchar_t c);
	bool IsDigit(wchar_t c);
	bool IsGraph(wchar_t c);
	bool IsLower(wchar_t c);
	bool IsPrintable(wchar_t c);
	bool IsPunctuation(wchar_t c);
	bool IsSpace(wchar_t c);
	bool IsUpper(wchar_t c);
	bool IsXDigit(wchar_t c);

protected:
	char value;
	
};

#endif // NCHAR_H
