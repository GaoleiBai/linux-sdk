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
   
   
#include "testadministration.h"
#include "../LFC/LFC.h"

TestAdministration::TestAdministration()
{
}

TestAdministration::~TestAdministration()
{
}

int TestAdministration::Perform()
{
	Collection<UserInfo *> users = System::Users();
	Collection<GroupInfo *> groups = System::Groups();
	
	for (int i=0; i<users.Count(); i++) 
		StdOut::PrintLine(users[i]->ToText());
	StdOut::PrintLine();
	
	for (int i=0; i<groups.Count(); i++)
		StdOut::PrintLine(groups[i]->ToText());
	StdOut::PrintLine();
	
	StdOut::PrintLine(System::GetRealUser().ToText());
	StdOut::PrintLine();
	StdOut::PrintLine(System::GetEffectiveUser().ToText());
	StdOut::PrintLine();
	StdOut::PrintLine(System::GetRealGroup().ToText());
	StdOut::PrintLine();
	StdOut::PrintLine(System::GetEffectiveGroup().ToText());
	StdOut::PrintLine();
	
	users.DeleteAndClear();
	groups.DeleteAndClear();
	
	try { 
		System::Mount("/dev/sda3", "test", "fuseblk", 0, ""); 
	} catch (SystemException *e) { 
		delete e; 
	}
	try { 
		System::Umount("test"); 
	} catch (SystemException *e) { 
		delete e; 
	}
	
	Text hostname = System::GetHostName();
	try { System::SetHostName("pepito"); }
	catch (Exception *e) { delete e; }
	Text hostnamePepito = System::GetHostName();
	try { System::SetHostName(hostname); }
	catch (Exception *e) { delete e; }
	
	return 0;
}