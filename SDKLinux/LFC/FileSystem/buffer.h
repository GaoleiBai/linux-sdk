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
   
   
#ifndef BUFFER_H
#define BUFFER_H

#include "../n_object.h"
#include "ifile.h"

class Buffer : public NObject, public IFile {

public:
	Buffer();
	Buffer(const char *buffer, int lonBuffer);
	Buffer(const Buffer &b);
	Buffer(const Buffer *b);
	virtual ~Buffer();
	
	virtual off_t FSetStart();
	virtual off_t FSetEnd();
	virtual off_t FSet(int position);
	virtual off_t FGet();
	virtual int Write(const char *buffer, int lonBuffer);
	virtual int Read(char *buffer, int lonBuffer);
	
	int Length();
	int FindIx(const Buffer &b);
	Buffer SubBuffer(int ix);
	Buffer SubBuffer(int ix, int length);
	
	char &operator[](int ix);
	bool operator==(const Buffer &b);
	bool operator!=(const Buffer &b);
	Buffer operator+(const Buffer &b);
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
private:
	char *buffer;
	int capacity;
	int lonBuffer;
	int position;
	
	void expandBuffer(int neededCapacity);
	
};

#endif // BUFFER_H
