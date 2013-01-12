#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include "../n_object.h"
#include "ifile.h"

class Serializator : public NObject {

public:
	Serializator(const IFile &file);
	virtual ~Serializator();
	
	void Put(const NObject &o);
	void Put(char n);
	void Put(short n);
	void Put(int n);
	void Put(long n);
	void Put(long long n);
	void Put(unsigned char n);
	void Put(unsigned short n);
	void Put(unsigned int n);
	void Put(unsigned long n);
	void Put(unsigned long long n);
	void Put(float n);
	void Put(double n);
	void Put(long double n);
	
	NObject *GetNObject();
	char GetChar();
	short GetShort();
	int GetInt();
	long GetLong();
	long long GetLongLong();
	unsigned char GetUChar();
	unsigned short GetUShort();
	unsigned int GetUInt();
	unsigned long GetULong();
	unsigned long long GetULongLong();
	float GetFloat();
	double GetDouble();
	long double GetLongDouble();
	
private:
	IFile *file;
	
	void ensureRead(char *buffer, int lonBuffer);

};

#endif // SERIALIZATOR_H
