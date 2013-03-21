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
#include "Tests.h"
#include "../LFC/LFC.h"

Tests::Tests()
{
	
}

Tests::~Tests()
{
	
}

int Tests::Perform()
{
	lfc_init(); // lfc initialization
	
	//Text t = StdIn::GetLine();
	
	StdOut::PrintLine("hello world");
	
	if (TestSerialization::Perform() != 0) {
		StdOut::PrintLine("TestSerialization::Perform error!!!");
		return -1;
	}
	
	if (TestNumeric::Perform() != 0) {
		StdOut::PrintLine("TestNumeric::Perform error!!!");
		return -1;
	}
	
	if (TestWindow::Perform() != 0) {
		StdOut::PrintLine("TestWindow::Perform error!!!");
		return -1;
	}
	
	TestRandom::Perform();
	
	if (TestSQLite3::Perform() != 0) {
		StdOut::PrintLine("TestSQLite3::Perform error!!!");
		return -1;
	}
	
	if (TestNetwork::Perform() != 0) {
		StdOut::PrintLine("TestNetwork::Perform error!!!");
		return -1;
	}
	
	if (TestThread::Perform() != 0) {
		StdOut::PrintLine("TestThread::Perform error");
		return -1;
	}
	
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
	
	if (TestSerialPort::Perform() != 0) {
		StdOut::PrintLine("TestSerialPort::Perform error!!!");
		return -1;
	}
	
	return 0;
}