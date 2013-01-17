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
   
   
#include "testnumeric.h"
#include "../LFC/LFC.h"

TestNumeric::TestNumeric()
{
}

TestNumeric::~TestNumeric()
{
}

int TestNumeric::Perform()
{
	NBool b = false;
	
	NChar c = 'c';
	NShort s = 5001;
	NInt i = 2345678;
	NLong l = 200167896;
	NLongLong ll = 200167896345;
	
	NUChar nc = 'c';
	NUShort ns = 5001;
	NUInt ni = 2345678;
	NULong nl = 200167896;
	NULongLong nll = 200167896345;

	NChar mc = -'c';
	NShort ms = -5001;
	NInt mi = -2345678;
	NLong ml = -200167896;
	NLongLong mll = -200167896345;
	
	NFloat f = -1234.5f;
	NDouble d = 128.765567;
	NLongDouble ld = -1e900l;

	return 0;
}

