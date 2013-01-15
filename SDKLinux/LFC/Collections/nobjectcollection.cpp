/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva
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
   
   
#include "nobjectcollection.h"
#include "collection.h"
#include "../Text/text_buffer.h"
#include "../Text/text.h"
#include "../FileSystem/serializator.h"
#include <typeinfo>

NObjectCollection::NObjectCollection() : Collection<NObject *>()
{
}

NObjectCollection::NObjectCollection(const NObject *t[]) : Collection<NObject *>((NObject* const*)t)
{
}

NObjectCollection::NObjectCollection(int size) : Collection<NObject *>(size)
{
}

NObjectCollection::NObjectCollection(const NObjectCollection &c) : Collection<NObject *>(c)
{
}

NObjectCollection::~NObjectCollection()
{
}

void NObjectCollection::Add(const NObject *o)
{
	if (o == NULL)
		throw new CollectionException("Cannot add NULL references", __FILE__, __LINE__, __func__);
		
	Collection<NObject *>::Add((NObject *)o);
}

void NObjectCollection::QuickSort()
{
	Collection<NObject *>::QuickSort(compare);
}

int NObjectCollection::BinarySearchIx(const NObject *o)
{
	return Collection<NObject *>::BinarySearchIx((NObject *)o, compare);
}

int NObjectCollection::compare(const void *u, const void *v)
{
	NObject **uu = (NObject **)u;
	NObject **vv = (NObject **)v;
	return (*uu)->Compare(**vv);
}

NObject *NObjectCollection::NewInstance()
{
	return new NObjectCollection();
}

Text NObjectCollection::ToText()
{
	TextBuffer b;
	for (int i=0; i<numObjects; i++) b.AppendLine(objects[i]->ToText());
	return b.ToText();
}

int NObjectCollection::Compare(const NObject &o)
{
	if (typeid(o) != typeid(NObjectCollection))
		throw new CollectionException("Trying to compare NObjectCollection to a different kind of object", __FILE__, __LINE__, __func__);
		
	return Compare((NObjectCollection &)o);
}

int NObjectCollection::Compare(const NObjectCollection &c)
{
	int diff = numObjects - c.numObjects;
	if (diff != 0) return diff;
	for (int i=0; i<numObjects; i++) {
		diff = ((NObject *)objects[i])->Compare(*((NObject *)c.objects[i]));
		if (diff != 0) return diff;
	}
	return 0;
}

void NObjectCollection::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(numObjects);
	for (int i=0; i<numObjects; i++) ((Serializator *)&s)->Put(*objects[i]);
}

void NObjectCollection::Deserialize(const Serializator &s)
{
	numObjects = ((Serializator *)&s)->GetInt();
	size = numObjects;
	objects = new NObject *[size];
	for (int i = 0; i<numObjects; i++)
		objects[i] = ((Serializator *)&s)->GetNObject();
}
