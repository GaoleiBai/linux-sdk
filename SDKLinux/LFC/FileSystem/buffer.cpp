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
