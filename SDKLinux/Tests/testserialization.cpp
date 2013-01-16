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
   
   
#include "testserialization.h"
#include "SerializationHelpClasses/helpclass.h"

TestSerialization::TestSerialization()
{
}

TestSerialization::~TestSerialization()
{
}

int TestSerialization::Perform()
{
	try {
		Text t("Hola mundo");
		HelpClass h;
		NObjectRegistry::Register(h);
		
		Buffer b;
		Serializator s(b);
		s.Put(t);
		
		b.FSetStart();
		Text *tt = (Text *)s.GetNObject();
		delete tt;
		
		b.FSetStart();
		s.Put(h);
		
		b.FSetStart();
		HelpClass *hh = (HelpClass *)s.GetNObject();
		delete hh;
		
		File::WriteAllBytes("SerializationTest.bin", b);
		
		File f("SerializationTest.bin", FO_ReadOnly);
		f.Open();
		Serializator ss(f);
		HelpClass *hhh = (HelpClass *)ss.GetNObject();
		f.Close();
		delete hhh;
		
		int kk = 0;
	} catch (Exception *e) {
		delete e;
	}
	
	return 0;
}

