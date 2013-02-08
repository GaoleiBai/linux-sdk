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
#include <string.h>
#include <typeinfo>
#include <unistd.h>
#include <time.h>


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
	int escrito = 0;
	while (escrito < lonBuffer) {
		int res = file->Write(buffer + escrito, lonBuffer - escrito > 1000 ? 1000 : lonBuffer - escrito);
		if (res == 0)
			throw new FileSystemException("It seems that the stream has suddently been closed.", __FILE__, __LINE__, __func__);
		escrito += res;
	}
}

void Serializator::Put(const NObject &o) 
{
	char strName[1000];
	strcpy(strName, typeid(o).name());
	unsigned char namelen = strlen(strName);
	unsigned char signature = 0x000000CC;

	file->Write((char *)&signature, sizeof(signature));
	file->Write((char *)&namelen, sizeof(namelen));
	file->Write(strName, namelen);
	((NObject *)&o)->Serialize(*this);
}

void Serializator::Put(bool b)
{
	file->Write((char *)&b, sizeof(b));	
}

void Serializator::Put(char n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(short n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(int n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(long long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned char n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned short n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned int n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(unsigned long long n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(float n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(double n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Put(long double n)
{
	file->Write((char *)&n, sizeof(n));
}

void Serializator::Get(char *buffer, int lonBuffer)
{
	int timecount = readTimeout;
	int leido = 0;
	while (leido < lonBuffer) {
		int res = file->Read(buffer + leido, lonBuffer - leido);
		if (res == 0) {	// Waits until timeout goes
			timecount -= READ_TIMEOUT_STEP;
			if (timecount < 0)
				throw new FileSystemException("Read timeout exception", __FILE__, __LINE__, __func__);
			file->WaitForDataComming(READ_TIMEOUT_STEP);
		} else {
			leido += res;
		}
	}
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
