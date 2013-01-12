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
	
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual NObject *Deserialize(const Serializator &s);
	
protected:
	static int compare(const void *u, const void *v);

};

#endif // NOBJECTCOLLECTION_H
