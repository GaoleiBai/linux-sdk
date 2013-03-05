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
   
   
#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#define READ_TIMEOUT_STEP 20000

#include "../n_object.h"
#include "ifile.h"

class Serializator : public NObject {

public:
	Serializator(const IFile &file);
	virtual ~Serializator();

	void Put(char *buffer, int lonBuffer);
	void Put(const NObject &o);
	void Put(bool n);
	void Put(char n);
	void Put(wchar_t n);
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
	
	void Get(char *buffer, int lonBuffer);
	NObject *GetNObject();
	bool GetBool();
	char GetChar();
	wchar_t GetWChar();
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
	
	unsigned long GetReadTimeout();
	void SetReadTimeout(unsigned long nanoseconds);
	
private:
	IFile *file;
	unsigned long readTimeout;
	
};

#endif // SERIALIZATOR_H
