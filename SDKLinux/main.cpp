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
   
   
#include <stdio.h>
#include "./LFC/LFC.h"
#include "./Tests/Tests.h"

int main(int argc, char **argv)
{
	lfc_init(); // lfc initialization
	
	StdOut::PrintLine("hello world");
	
	if (TestDelegation::Perform() != 0) {
		StdOut::PrintLine("TestDelegation::Perform error");
		return -1;
	}
	
	if (TestText::PerformAnsi() != 0) {
		StdOut::PrintLine("PerformAnsi error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestText::PerformWide() != 0) {
		StdOut::PrintLine("PerformWide error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestDirectory::Perform() != 0) {
		StdOut::PrintLine("TestDirectory::Perform error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestDateTime::Perform() != 0) {
		StdOut::PrintLine("TestDateTime::Perform error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestAdministration::Perform() != 0) {
		StdOut::PrintLine("TestAdministration::Perform error!!!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestFile::Perform() != 0) {
		StdOut::PrintLine("TestFile::Perform error!!!");
		return -1;
	}
	
	if (TestCollection::Perform() != 0) {
		StdOut::PrintLine("TestCollection::Perform error!!!");
		return -1;
	}
	
	if (TestDictionary::Perform() != 0) {
		StdOut::PrintLine("TestDictionary::Perform error!!!");
		return -1;
	}
	
	if (TestBuffer::Perform() != 0) {
		StdOut::PrintLine("TestBuffer::Perform error!!!");
		return -1;
	}
	
	if (TestSerialization::Perform() != 0) {
		StdOut::PrintLine("TestSerialization::Perform error!!!");
		return -1;
	}
	
	if (TestSerialPort::Perform() != 0) {
		StdOut::PrintLine("TestSerialPort::Perform error!!!");
		return -1;
	}
	
	if (TestNumeric::Perform() != 0) {
		StdOut::PrintLine("TestNumeric::Perform error!!!");
		return -1;
	}
	
	return 0;
}
