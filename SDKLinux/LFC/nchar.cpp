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
   
   
#include "nchar.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include "Devices/stdout.h"
#include <limits.h>
#include <typeinfo>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

NChar::NChar()
{
	value = 0;
}

NChar::NChar(char c)
{
	value = c;
}

NChar::NChar(const NChar &c)
{
	value = c.value;
}

NChar::~NChar()
{
}

char NChar::MaxValue() 
{
	return SCHAR_MAX;
}

char NChar::MinValue()
{
	return SCHAR_MIN;
}

char NChar::Parse(const Text &text)
{
	char c = 0;
	if (!TryParse(text, c))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return c;
}

bool NChar::TryParse(const Text &text, char &c)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	errno = 0;
	long long l = atoll(cadena);
	if (errno != 0) return false;
	if (l > MaxValue() || l < MinValue()) return false;
	c = l;
	return true;
}

Text NChar::ToText(const Text &format)
{
	char cadena[1001];
	((Text *)&format)->GetAnsiString(cadena, 1000);
	
	char res[1001];
	sprintf(res, cadena, value);
	return (Text)res;
}

char &NChar::Value()
{
	return value;
}

NObject *NChar::NewInstance()
{
	return new NChar();
}

Text NChar::ToText()
{
	const char cadena[] = { value, 0 };
	return (Text)cadena;
}

int NChar::Compare(const NObject &o)
{
	long long vo = ((NObject *)&o)->ToLongLong();		
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;	
}

int NChar::Compare(const NChar &c)
{
	if (value > c.value) return 1;
	else if (value < c.value) return -1;
	else return 0;
}

void NChar::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NChar::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetChar();
}

long long NChar::ToLongLong()
{
	return value;
}

long double NChar::ToLongDouble()
{
	return value;
}

int NChar::COMPARER(const void *u, const void *v)
{
	char *uu = (char *)u;
	char *vv = (char *)v;
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	return 0;
}

bool NChar::IsAlpha(char c)
{
	return isalpha(c);
}

bool NChar::IsAlphaNumeric(char c)
{
	return isalnum(c);
}

bool NChar::IsAscii(char c)
{
	return isascii(c);
}

bool NChar::IsBlank(char c)
{
	return isblank(c);
}

bool NChar::IsControl(char c)
{
	return iscntrl(c);
}

bool NChar::IsDigit(char c)
{
	return isdigit(c);
}

bool NChar::IsGraph(char c)
{
	return isgraph(c);
}

bool NChar::IsLower(char c)
{
	return islower(c);
}

bool NChar::IsPrintable(char c)
{
	return isprint(c);
}

bool NChar::IsPunctuation(char c)
{
	return ispunct(c);
}

bool NChar::IsSpace(char c)
{
	return isspace(c);
}

bool NChar::IsUpper(char c)
{
	return isupper(c);
}

bool NChar::IsXDigit(char c)
{
	return isxdigit(c);
}
