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
   
   
#include "serializator.h"
#include "filesystemexception.h"
#include "../Text/text.h"
#include "../nobjectregistry.h"
#include "../Devices/stdout.h"
#include "../System/system.h"
#include <string.h>
#include <typeinfo>
#include <unistd.h>
#include <time.h>
#include <ctype.h>


Serializator::Serializator(const IFile &file)
{
	this->file = (IFile *)&file;
	readTimeout = 60000000;
}

Serializator::~Serializator()
{
	
}

void Serializator::Put(char *buffer, int lonBuffer)
{
	file->Write(buffer, lonBuffer);
}

void Serializator::Put(const NObject &o) 
{
	char strName[1000];
	((NObject *)&o)->ClassName().GetAnsiString(strName, 1000);
	
	unsigned char namelen = strlen(strName);
	unsigned char signature = 0x000000CC;

	Put((char *)&signature, sizeof(signature));
	Put((char *)&namelen, sizeof(namelen));
	Put(strName, namelen);
	((NObject *)&o)->Serialize(*this);
}

void Serializator::Put(bool b)
{
	Put((char *)&b, sizeof(b));	
}

void Serializator::Put(char n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(short n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(int n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(long n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(long long n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned char n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned short n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned int n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned long n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned long long n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(float n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(double n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Put(long double n)
{
	Put((char *)&n, sizeof(n));
}

void Serializator::Get(char *buffer, int lonBuffer)
{
	file->Read(buffer, lonBuffer, readTimeout);
}

NObject *Serializator::GetNObject()
{
	char strName[1000];
	unsigned char namelen = 0;
	unsigned char signature = 0;

	Get((char *)&signature, sizeof(signature));
	if (signature != 0x00CC) 
		throw new FileSystemException((Text)"No valid class found in file.", __FILE__, __LINE__, __func__);
	Get((char *)&namelen, sizeof(namelen));
	Get(strName, namelen);
	strName[namelen] = 0;
	
	NObject *o = NObjectRegistry::GetInstance(strName);
	o->Deserialize(*this);
	return o;
}

bool Serializator::GetBool()
{
	bool n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

char Serializator::GetChar()
{
	char n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

short Serializator::GetShort()
{
	short n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

int Serializator::GetInt()
{
	int n = 0;
	Get((char *)&n, sizeof(n));
	return n;	
}

long Serializator::GetLong()
{
	long n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

long long Serializator::GetLongLong()
{
	long long n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

unsigned char Serializator::GetUChar()
{
	unsigned char n = 0;
	Get((char *)&n, sizeof(n));
	return n;	
}

unsigned short Serializator::GetUShort()
{
	unsigned short n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

unsigned int Serializator::GetUInt()
{
	unsigned int n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

unsigned long Serializator::GetULong()
{
	unsigned long n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

unsigned long long Serializator::GetULongLong()
{
	unsigned long long n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

float Serializator::GetFloat()
{
	float n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

double Serializator::GetDouble()
{
	double n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

long double Serializator::GetLongDouble()
{
	long double n = 0;
	Get((char *)&n, sizeof(n));
	return n;
}

unsigned long Serializator::GetReadTimeout()
{
	return readTimeout;
}

void Serializator::SetReadTimeout(unsigned long nanoseconds)
{
	readTimeout = nanoseconds;
}
