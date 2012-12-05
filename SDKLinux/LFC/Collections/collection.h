#ifndef ARRAY_H
#define ARRAY_H

#include "../n_object.h"
#include "collection_exception.h"

template <class T>
class Collection : public NObject {

public:
	Collection();
	Collection(int size);
	Collection(T t[]);
	Collection(const Collection<T> &c);
	virtual ~Collection();

	void Add(T o);
	void AddRange(T t[]);
	void AddRange(Collection<T> &c);
	void Remove(T o);
	void Compact();
	void Clear();
	void DeleteAndClear();
	int Count();
	bool Contains(T o);
	
	T &operator [](int ix);

private:
	T *objects;
	int size;
	int numObjects;

};

template<class T>
Collection<T>::Collection()
{
	size = 1;
	objects = new T[size];
	numObjects = 0;	
}

template<class T>
Collection<T>::Collection(int size)
{
	this->size = size < 4 ? 4 : size;
	objects = new T[size];
	numObjects = 0;
}

template<class T>
Collection<T>::Collection(T t[])
{
	int tsize = 0;
	T *tt = t;
	while (*tt++) tsize++; 
	
	size = tsize > 0 ? tsize : 1;
	objects = new T[size];
	numObjects = tsize;
	
	tt = t;
	T *oo = objects;
	while (*tt) *oo++ = *tt++;
}

template<class T>
Collection<T>::Collection(const Collection<T> &c)
{
	size = c.size > 0 ? c.size : 1;
	objects = new T[size];
	numObjects = size;
	
	T *cc = c.objects;
	T *oo = objects;
	while (*cc) *oo++ = *cc++;
}

template<class T>
Collection<T>::~Collection()
{
	delete objects;
}

template<class T>
void Collection<T>::Add(T o)
{
	if (numObjects == size) {
		T *p = new T[2 * size];
		for (int i = 0; i < size; i++) p[i] = objects[i];
		delete objects;
		objects = p;
		size *= 2;
	}
	
	objects[numObjects++] = o;
}

template<class T>
void Collection<T>::AddRange(T t[])
{
	T *tt = t;
	while (*tt) Add(*tt++);
}

template<class T>
void Collection<T>::AddRange(Collection<T> &c)
{
	size = numObjects + c.numObjects;
	if (size < 1) size = 1;
	T *q = new T[size + c.size];
	for (int i=0; i<numObjects; i++) q[i] = objects[i];
	for (int i=0; i<c.numObjects; i++) q[i + numObjects] = c.objects[i];
	delete objects;
	objects = q;
	numObjects += c.numObjects;
}

template<class T>
void Collection<T>::Remove(T o)
{
	for (int i=0; i<numObjects; i++) {
		if (objects[i] != o) continue;
		numObjects--;
		for (int j = 0; j < numObjects; j++) objects[j] = objects[j + 1];
		break;
	}
}

template<class T>
void Collection<T>::Clear()
{
	delete objects;
	size = 1;
	objects = new NObject*[size];
	numObjects = 0;
}

template<class T>
void Collection<T>::DeleteAndClear()
{
	if (is_pointer<T>::value) for (int i=0; i<numObjects; i++) delete objects[i];
	Clear();
}

template<class T>
void Collection<T>::Compact()
{
	if (size == numObjects || numObjects < 1) return;
	T *q = new T[numObjects];
	for (int i=0; i<numObjects; i++) q[i] = objects[i];
	delete objects;
	objects = q;
	size = numObjects;
}

template<class T>
int Collection<T>::Count()
{
	return numObjects;
}

template<class T>
bool Collection<T>::Contains(T o)
{
	for (int i=0; i<numObjects; i++) {
		if (o == objects[i]) return true;
	}
	
	return false;
}

template<class T>
T &Collection<T>::operator[](int ix)
{
	if (ix < 0 || ix > numObjects) new CollectionException("Index out of bounds");
	return objects[ix];
}


#endif // ARRAY_H
