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
	
	virtual Text ToText();
	virtual void Serialize(const Serializator &s);
	virtual NObject *Deserialize(const Serializator &s);
	
private:
	char *buffer;
	int capacity;
	int lonBuffer;
	int position;
	
	void expandBuffer(int neededCapacity);
	
};

#endif // BUFFER_H
