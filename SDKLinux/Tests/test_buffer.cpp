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
#include "test_buffer.h"

TestBuffer::TestBuffer()
{
}

TestBuffer::~TestBuffer()
{
}

int TestBuffer::Perform()
{
	Buffer b("aaaa", 4);
	b.Write("bbbb", 4);
	b.Write("cccc", 4);
	
	if (b.SubBuffer(8).Length() != 4){
		StdOut::PrintLine("Buffer::SubBuffer didn't work!!!");
		return -1;
	}
	
	b.FSet(4);
	b.Write("dddd", 4);
	if (b.ToText() != "aaaaddddcccc") {
		StdOut::PrintLine("Buffer::FSet didn't work!!!");
		return -1;
	}
	
	if (b.FGet() != 8) {
		StdOut::PrintLine("Buffer::FGet didn't work!!!");
		return -1;
	}
	
	b.FSetStart();
	if (b.FGet() != 0) {
		StdOut::PrintLine("Buffer::FSetStart didn't work!!!");
		return -1;
	}
	
	b.Write("eeee", 4);
	if (b.ToText() != "eeeeddddcccc") {
		StdOut::PrintLine("Buffer::Write didn't work!!!");
		return -1;
	}
	
	b.FSetEnd();
	b.Write("vvvv", 4);
	if (b.ToText() != "eeeeddddccccvvvv") {
		StdOut::PrintLine("Buffer::FSetEnd didn't work!!!");
		return -1;
	}
	
	if (b.SubBuffer(0, 4).ToText() != "eeee") {
		StdOut::PrintLine("Buffer::SubBuffer didn't work!!!");
		return -1;
	}
	
	if (b.SubBuffer(12).ToText() != "vvvv") {
		StdOut::PrintLine("Buffer::SubBuffer didn't work!!!");
		return -1;
	}
	
	if (b.SubBuffer(4).ToText() != "ddddccccvvvv") {
		StdOut::PrintLine("Buffer::SubBuffer didn't work!!!");
		return -1;
	}
	
	if (b.SubBuffer(4).SubBuffer(4, 4).ToText() != "cccc") {
		StdOut::PrintLine("Buffer::SubBuffer didn't work!!!");
		return -1;
	}
	
	const char *cadena = "eeeeddddccccvvvv";
	for (int i=0; i<b.Length(); i++) {
		if (b[i] == cadena[i]) continue;
		StdOut::PrintLine("Buffer::operator[](int ix) didn't work!!!");
		return -1;
	}
	
	if (b == b.SubBuffer(0, 4) + b.SubBuffer(4)) {
		StdOut::PrintLine("Buffer::operator+ didn't work!!!");
		return -1;
	}
	
	Buffer b2;
	char c;
	for (int i=0; i<100000; i++) {
		c = 48 + i % 32;
		b2.Write(&c, 1);
	}
	if (b2.ToText().Length() != 100000) {
		StdOut::PrintLine("Writing more than 1000 chars to buffer didn't work");
		return -1;
	}
	for (int i=0; i<100000; i++) {
		c = 48 + i % 32;
		if (b2[i] == c) continue;
		StdOut::PrintLine("Buffer not propertly populated");
		return -1;
	}
	
	return 0;
}

