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
#include "testdelegation.h"
#include "../LFC/LFC.h"
#include "stdio.h"

TestDelegation::TestDelegation()
{
}

TestDelegation::~TestDelegation()
{
}

int TestDelegation::Perform()
{
	class A : public NObject
	{
	public:
		A() {};
		void *amethod(char *param) { 
			StdOut::PrintLine((Text)"Hello " + param + " world!!!");
			return (void *)"Wolomolo!!!"; 
		};
	};
	
	A aa;
	NDelegation d(&aa, (Delegate)&A::amethod);
	Text wolomolo = (char *)d.Execute((char *)"Aparam");
	StdOut::PrintLine(wolomolo);
	
	return 0;
}

