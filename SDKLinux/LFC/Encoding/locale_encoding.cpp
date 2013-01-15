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
   
   
#include <locale.h>
#include "../Text/text.h"
#include "./locale_encoding.h"

Locale::Locale()
{
}

Locale::~Locale()
{
}

void Locale::SetLocale(Text &locale)
{
	setlocale(LC_ALL, "C");
	int len = locale.length;
	char *loc = new char[locale.length + 1];
	locale.GetAnsiString(loc, len);
	setlocale(LC_ALL, loc);
	delete loc;
}

void Locale::SetLocale(const char *locale)
{
	setlocale(LC_ALL, locale);	
}

void Locale::SetLocale(const wchar_t *locale)
{
	Text loc(locale);
	SetLocale(loc);
}

