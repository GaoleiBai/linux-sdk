/* 
* LFC Library - Linux toolkit
* 
* Copyright (C) 2012, 2013 Daniel Mosquera Villanueva 
* (milkatoffeecuco@gmail.com)
* This file is part of LFC Library.
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*
**/
#ifndef NOBJECTCOLLECTION_H
#define NOBJECTCOLLECTION_H

#include "collection.h"
#include "../n_object.h"

class NObjectCollection : public Collection<NObject *>, public NObject {

public:
	NObjectCollection();
	NObjectCollection(int size);
	NObjectCollection(const NObject *t[]);
	NObjectCollection(const NObjectCollection &c);
	virtual ~NObjectCollection();
	
	virtual void Add(const NObject *o);
	void QuickSort();
	int BinarySearchIx(const NObject *o);
	virtual int Compare(const NObjectCollection &c);
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
protected:
	static int compare(const void *u, const void *v);

};

#endif // NOBJECTCOLLECTION_H
