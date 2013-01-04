#ifndef BUFFER_H
#define BUFFER_H

#include "../n_object.h"
#include "ifile.h"

class Buffer : NObject, IFile {

public:
	Buffer();
	Buffer(const Buffer &b);
	Buffer(const Buffer *b);
	virtual ~Buffer();
	
	virtual off_t FSetStart();
	virtual off_t FSetEnd();
	virtual off_t FSet(int position);
	virtual off_t FGet();
	virtual void Write(char *buffer, int lonBuffer);
	virtual int Read(char *buffer, int lonBuffer);
	
	Text ToText();
	
private:
	char *buffer;
	int capacity;
	int lonBuffer;
	int position;
	
	void expandBuffer(int neededCapacity);
	
};

#endif // BUFFER_H
