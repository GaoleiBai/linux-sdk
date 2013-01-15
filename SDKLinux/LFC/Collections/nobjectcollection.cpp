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
