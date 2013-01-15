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
   
   
#include "../LFC/LFC.h"
#include "testfile.h"

TestFile::TestFile()
{
}

TestFile::~TestFile()
{
}

int TestFile::Perform()
{
	try {
		Text fileToTest = "/var/log/dpkg.log";
		
		if (!File::Exists(fileToTest)) {
			StdOut::PrintLine("No se puede acceder al fichero de pruebas.");
			return -1;
		}
		
		try { File::Copy(fileToTest, "prueba"); }
		catch (FileSystemException * e) {
			StdOut::PrintLine("File copy didn't work");
			delete e;
			return -1;
		}
		
		Text f1 = File::ReadAllText(fileToTest);
		Text f2 = File::ReadAllText("prueba");
		if (f1 != f2) {
			StdOut::PrintLine("File copy is not exact");
			return -1;
		}
		
		Buffer b1 = File::ReadAllBytes(fileToTest);
		Buffer b2 = File::ReadAllBytes("prueba");
		if (b1 != b2) {
			StdOut::PrintLine("File copy is not exact");
			return -1;
		}
		
		if (b1.ToText() != f2) {
			StdOut::PrintLine("Buffer and text don't match");
			return -1;
		}
		
		File::WriteAllBytes("prueba2", b1);
		Buffer b3 = File::ReadAllBytes("prueba2");
		if (b3 != b1) {
			StdOut::PrintLine("WriteAllBytes didn't work");
			return -1;
		}
		
		File::Move("prueba2", "prueba3");
		Buffer b4 = File::ReadAllBytes("prueba3");
		if (b1 != b4 || File::Exists("prueba2")) {
			StdOut::PrintLine("Move didn't work");
			return -1;
		}
		
		Collection<Text *> lines = File::ReadAllLines(fileToTest);

		Text t = Text::Join(lines, "\n");
		Text u = File::ReadAllText(fileToTest);
		
		if (t != u) {
			StdOut::PrintLine("Diferent results between ReadAllLines and ReadAllText");
			return -1;
		}
		
		lines.DeleteAndClear();
		
		File::Link("prueba3", "prueba4");
		if (!File::Exists("prueba4")) {
			StdOut::PrintLine("Link didn't work");
			return -1;
		}
		
		File::Symlink("prueba3", "prueba5");
		if (!File::Exists("prueba5")) {
			StdOut::PrintLine("SymLink didn't work");
			return -1;
		}
		
		File::Delete("prueba4");
		if (!File::Exists("prueba3") || File::Exists("prueba4")) {
			StdOut::PrintLine("Delete didn't work");
			return -1;
		}
		
		File::Delete("prueba5");
		if (!File::Exists("prueba3") || File::Exists("prueba5")) {
			StdOut::PrintLine("Delete didn't work");
			return -1;
		}
		
		File::Delete("prueba");
		File::Delete("prueba3");
		if (File::Exists("prueba") || File::Exists("prueba3")) {
			StdOut::PrintLine("Delete didn't work");
			return -1;
		}
		
	} catch (Exception *e) {
		delete e;
		return -1;
	}
	
	return 0;
}
