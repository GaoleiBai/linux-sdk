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
#ifndef NWCHAR_H
#define NWCHAR_H

#include "n_object.h"

class Text;

class NWChar : public NObject {

public:
	NWChar();
	NWChar(wchar_t c);
	NWChar(const NWChar &c);
	virtual ~NWChar();
	
	static wchar_t MaxValue();
	static wchar_t MinValue();
	static wchar_t Parse(const Text &t);
	static bool TryParse(const Text &t, wchar_t &c);
	Text ToText(const Text &format);
	
	wchar_t &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual int Compare(const NWChar &c);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	virtual long long ToLongLong();
	virtual long double ToLongDouble();
	
	static int COMPARER(const void *u, const void *v);
	
	bool IsAlpha(wchar_t c);
	bool IsAlphaNumeric(wchar_t c);
	bool IsControl(wchar_t c);
	bool IsBlank(wchar_t c);
	bool IsDigit(wchar_t c);
	bool IsGraph(wchar_t c);
	bool IsLower(wchar_t c);
	bool IsPrintable(wchar_t c);
	bool IsPunctuation(wchar_t c);
	bool IsSpace(wchar_t c);
	bool IsUpper(wchar_t c);
	bool IsXDigit(wchar_t c);

protected:
	wchar_t value;

};

#endif // NWCHAR_H
