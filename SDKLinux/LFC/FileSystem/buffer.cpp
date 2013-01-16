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
   
   
#include "buffer.h"
#include "filesystemexception.h"
#include "../Text/text.h"
#include "../FileSystem/serializator.h"
#include <string.h>

void Buffer::expandBuffer(int neededCapacity)
{
	if (capacity >= neededCapacity) return;
	
	capacity = neededCapacity + 10000;
	char *q = new char[capacity];
	memcpy(q, buffer, lonBuffer);
	delete buffer;
	buffer = q;
}

Buffer::Buffer()
{
	position = 0;
	capacity = 10000;
	lonBuffer = 0;
	buffer = new char[capacity];
}

Buffer::Buffer(const char *buffer, int lonBuffer)
{
	capacity = lonBuffer;
	this->lonBuffer = lonBuffer;
	this->buffer = new char[capacity];
	memcpy(this->buffer, buffer, lonBuffer);
	position = lonBuffer;
}

Buffer::Buffer(const Buffer &b)
{
	position = b.position;
	capacity = b.capacity;
	lonBuffer = b.lonBuffer;
	buffer = new char[capacity];
	memcpy(buffer, b.buffer, lonBuffer);
}

Buffer::Buffer(const Buffer *b)
{
	position = b->position;
	capacity = b->capacity;
	lonBuffer = b->lonBuffer;
	buffer = new char[capacity];
	memcpy(buffer, b->buffer, lonBuffer);
}

Buffer::~Buffer()
{
	delete buffer;
}

int Buffer::Write(const char *buffer, int lonBuffer)
{
	expandBuffer(position + lonBuffer);
	memcpy(this->buffer + position, buffer, lonBuffer);
	int newLonBuffer = position + lonBuffer;
	if (this->lonBuffer < newLonBuffer) this->lonBuffer = newLonBuffer;
	position += lonBuffer;
	return lonBuffer;
}

int Buffer::Read(char *buffer, int lonBuffer)
{
	int leer = position + lonBuffer >= this->lonBuffer ? leer = this->lonBuffer - position : lonBuffer;
	if (!leer) return 0;
	
	memcpy(buffer, this->buffer + position, leer);
	position += leer;
	return leer;
}

off_t Buffer::FSetStart()
{
	position = 0;
}

off_t Buffer::FSetEnd()
{
	position = lonBuffer;
}

off_t Buffer::FSet(int position)
{
	if (position < 0)
		throw new FileSystemException("Position cannot be lower than 0", __FILE__, __LINE__, __func__);
	if (position >= lonBuffer)
		throw new FileSystemException("Cannot set position beyond the end of the buffer", __FILE__, __LINE__, __func__);
	this->position = position;
}

off_t Buffer::FGet()
{
	return position;
}

NObject *Buffer::NewInstance()
{
	return new Buffer();
}

Text Buffer::ToText()
{
	Text t(buffer, lonBuffer);
	return t;
}

int Buffer::Length()
{
	return lonBuffer;
}

int Buffer::FindIx(const Buffer &b)
{
	for (int i=0; i<lonBuffer - b.lonBuffer + 1; i++) {
		for (int j=0; j<b.lonBuffer; j++) {
			if (buffer[i + j] != b.buffer[j]) break;
			if (j == b.lonBuffer - 1) return i;
		}
	}
	
	return -1;
}

Buffer Buffer::SubBuffer(int ix)
{
	if (ix < 0 || ix >= lonBuffer)
		throw new FileSystemException("Index out of bounds", __FILE__, __LINE__, __func__);
		
	Buffer b(buffer + ix, lonBuffer - ix);
	return b;
}

Buffer Buffer::SubBuffer(int ix, int length)
{
	if (ix < 0 || ix + length > lonBuffer)
		throw new FileSystemException("Index ot of bounds", __FILE__, __LINE__, __func__);
		
	Buffer b(buffer + ix, length);
	return b;
}

char &Buffer::operator [](int ix)
{
	if (ix < 0 || ix >= lonBuffer)
		throw new FileSystemException("Index out of bounds.", __FILE__, __LINE__, __func__);
		
	return buffer[ix];
}

bool Buffer::operator ==(const Buffer &b)
{
	if (lonBuffer != b.lonBuffer) return false;
	for (int i=0; i<lonBuffer; i++)
		if (buffer[i] != b.buffer[i])
			return false;
	return true;
}

bool Buffer::operator !=(const Buffer &b)
{
	return !(*this == b);
}

Buffer Buffer::operator +(const Buffer &b)
{
	Buffer q = *this;
	q.expandBuffer(q.lonBuffer + b.lonBuffer);
	memcpy(q.buffer + q.lonBuffer, b.buffer, b.lonBuffer);
	return q;
}

void Buffer::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(lonBuffer);
	((Serializator *)&s)->Put(buffer, lonBuffer);
}

void Buffer::Deserialize(const Serializator &s)
{
	lonBuffer = ((Serializator *)&s)->GetInt();
	capacity = lonBuffer;
	delete buffer;
	buffer = new char[capacity];
	((Serializator *)&s)->Get(buffer, lonBuffer);
}