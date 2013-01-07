#include "buffer.h"
#include "filesystemexception.h"
#include "../Text/text.h"
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
	position = 0;
	capacity = lonBuffer;
	this->lonBuffer = lonBuffer;
	this->buffer = new char[capacity];
	memcpy(this->buffer, buffer, lonBuffer);
}

Buffer::Buffer(const Buffer &b)
{
	position = 0;
	capacity = b.capacity;
	lonBuffer = b.lonBuffer;
	buffer = new char[capacity];
	memcpy(buffer, b.buffer, lonBuffer);
}

Buffer::Buffer(const Buffer *b)
{
	position = 0;
	capacity = b->capacity;
	lonBuffer = b->lonBuffer;
	buffer = new char[capacity];
	memcpy(buffer, b->buffer, lonBuffer);
}

Buffer::~Buffer()
{
	delete buffer;
}

void Buffer::Write(char *buffer, int lonBuffer)
{
	expandBuffer(position + lonBuffer);
	memcpy(this->buffer + position, buffer, lonBuffer);
	int newLonBuffer = position + lonBuffer;
	if (this->lonBuffer < newLonBuffer) this->lonBuffer = newLonBuffer;
	position += lonBuffer;
}

int Buffer::Read(char *buffer, int lonBuffer)
{
	if (position + lonBuffer > this->lonBuffer) 
		throw new FileSystemException("Cannot read beyond the end of the buffer", __FILE__, __LINE__, __func__);
	
	memcpy(buffer, this->buffer + position, lonBuffer);
	return lonBuffer;
}

off_t Buffer::FSetStart()
{
	position = 0;
}

off_t Buffer::FSetEnd()
{
	position = lonBuffer - 1;
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