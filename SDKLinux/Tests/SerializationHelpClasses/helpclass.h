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
   
   
#ifndef HELPCLASS_H
#define HELPCLASS_H

#include "../../LFC/LFC.h"

class HelpClass : public NObject {

public:
	HelpClass();
	virtual ~HelpClass();
	
	virtual NObject *NewInstance();
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
private:
	bool nbool;
	char nchar;
	short nshort;
	int nint;
	long nlong;
	long long nlonglong;
	unsigned char nuchar;
	unsigned short nushort;
	unsigned int nuint;
	unsigned long nulong;
	unsigned long long nulonglong;
	float nfloat;
	double ndouble;
	long double nlongdouble;
	Text *atext;
	DateTime *adatetime;
	NObjectCollection *nobjectcollection;
	NObjectDictionary *nobjectdictionary;
	Buffer *abuffer;
	TextBuffer *atextbuffer;
	NBool *nnbool;
	NChar *nnchar;
	NWChar *nnwchar;
	NShort *nnshort;
	NInt *nnint;
	NLong *nnlong;
	NLongLong *nnlonglong;
	NUChar *nnuchar;
	NUShort *nnushort;
	NUInt *nnuint;
	NULong *nnulong;
	NULongLong *nnulonglong;
	NFloat *nnfloat;
	NDouble *nndouble;
	NLongDouble *nnlongdouble;
	
};

#endif // HELPCLASS_H
