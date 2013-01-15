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
   
   
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "collection.h"
#include "collection_exception.h"
#include "../n_object.h"
#include "../Text/text.h"
#include <stdlib.h>

template<class K, class V>
class DictionaryEntry {
public:
	K Key;
	V Value;
	
	DictionaryEntry();
	DictionaryEntry(K key);
	DictionaryEntry(K key, V value);
	~DictionaryEntry();
	
};

template<class K, class V>
DictionaryEntry<K, V>::DictionaryEntry()
{
	
}

template<class K, class V>
DictionaryEntry<K, V>::DictionaryEntry(K key)
{
	Key = key;
}

template<class K, class V>
DictionaryEntry<K, V>::DictionaryEntry(K key, V value)
{
	Key = key;
	Value = value;
}

template<class K, class V>
DictionaryEntry<K, V>::~DictionaryEntry()
{
}

template<class K, class V>
class Dictionary {

public:
	Dictionary();
	Dictionary(int (*COMPARER)(const void *u, const void *v));
	virtual ~Dictionary();
	
	virtual void SetKey(K key, V value);
	bool GetKey(K key, V &value);
	void ClearKey(K key);
	bool ExistsKey(K key);
	void Clear();
	void Pack();
	void DeleteAndClearKey(K key);
	void DeleteAndClear();

	Collection<K> Keys();
	Collection<V> Values();
	
protected:
	DictionaryEntry<K, V> **entries;
	int numEntries;
	int capacity;
	static int (*KEY_COMPARER)(const void *u, const void *v);
	
	void ensureCapacity(int capacity);
	int binarySearchIx(K key);
	void deleteEntry(int ix);
	static int ENTRY_COMPARER(const void *u, const void *v);

};

template<class K, class V>
int (*Dictionary<K, V>::KEY_COMPARER)(const void *u, const void *v);

template<class K, class V>
Dictionary<K, V>::Dictionary()
{
	throw new CollectionException("Not implemented", __FILE__, __LINE__, __func__);
}

template<class K, class V>
Dictionary<K, V>::Dictionary(int (*COMPARER)(const void *u, const void *v))
{
	capacity = 0;
	numEntries = 0;
	KEY_COMPARER = COMPARER;
	entries = NULL;
	ensureCapacity(1000);
}

template<class K, class V>
Dictionary<K, V>::~Dictionary()
{
	Clear();
	delete entries;
}

template<class K, class V>
void Dictionary<K, V>::ensureCapacity(int capacity)
{
	if (this->capacity >= capacity) return;
	
	int newCapacity = capacity + 1000;
	DictionaryEntry<K, V> **q = new DictionaryEntry<K, V> *[newCapacity];
	for (int i=0; i<numEntries; i++)
		q[i] = entries[i];
	if (entries != NULL) delete entries;
	entries = q;
	this->capacity = newCapacity;
}

template<class K, class V>
int Dictionary<K, V>::binarySearchIx(K key)
{
	DictionaryEntry<K, V> *e = new DictionaryEntry<K, V>(key);
	void *q = bsearch(&e, entries, numEntries, sizeof(entries[0]), ENTRY_COMPARER);
	delete e;
	
	if (q == NULL) return -1;
	return ((unsigned long)q - (unsigned long)entries) / sizeof(entries[0]);
}

template<class K, class V>
int Dictionary<K, V>::ENTRY_COMPARER(const void *u, const void *v)
{
	DictionaryEntry<K, V> **uu = (DictionaryEntry<K, V> **)u;
	DictionaryEntry<K, V> **vv = (DictionaryEntry<K, V> **)v;
	
	K keys[2];
	keys[0] = (**uu).Key;
	keys[1] = (**vv).Key;
	return KEY_COMPARER((const void *)&keys[0], (const void *)&keys[1]);
}

template<class K, class V>
void Dictionary<K, V>::SetKey(K key, V value)
{
	int ix = binarySearchIx(key);
	if (ix != -1) {
		entries[ix]->Value = value;
	} else {
		ensureCapacity(numEntries + 1);
		
		// Create and insert the new entry
		DictionaryEntry<K, V> *e = new DictionaryEntry<K, V>(key, value);
		ix = numEntries;
		for (int i=numEntries-1; i>=0; i--) {
			if (KEY_COMPARER(&key, &entries[i]->Key) > 0) break;
			entries[i + 1] = entries[i];
			ix--;
		}
		entries[ix] = e;
		numEntries++;
	}
}

template<class K, class V>
bool Dictionary<K, V>::GetKey(K key, V &value)
{
	int ix = binarySearchIx(key);
	if (ix == -1) return false;
	value = entries[ix]->Value;
	return true;
}

template<class K, class V>
void Dictionary<K, V>::ClearKey(K key)
{
	int ix = binarySearchIx(key);
	if (ix == -1) return;
	
	delete entries[ix];
	numEntries--;
	for (int i=ix; i<numEntries; i++)
		entries[i] = entries[i + 1];
}

template<class K, class V>
bool Dictionary<K, V>::ExistsKey(K key)
{
	return binarySearchIx(key) != -1;
}

template<class K, class V>
void Dictionary<K, V>::Clear()
{
	for (int i=0; i<numEntries; i++)
		delete entries[i];
	numEntries = 0;
}

template<class K, class V>
void Dictionary<K, V>::Pack()
{
	if (numEntries == capacity || numEntries < 1) return;
	
	DictionaryEntry<K, V> **q = new DictionaryEntry<K, V> *[numEntries];
	for (int i=0; i<numEntries; i++) q[i] = entries[i];
	capacity = numEntries;
}

template<class K, class V>
void Dictionary<K, V>::DeleteAndClearKey(K key)
{
	int ix = binarySearchIx(key);
	if (ix == -1) return;
	
	delete entries[ix]->Key;
	delete entries[ix]->Value;
	delete entries[ix];
	
	numEntries--;
	for (int i = ix; i<numEntries; i++)
		entries[i] = entries[i + 1];
}

template<class K, class V>
void Dictionary<K, V>::DeleteAndClear()
{
	for (int i=0; i<numEntries; i++) {
		delete entries[i]->Key;
		delete entries[i]->Value;
		delete entries[i];
	}
	numEntries = 0;
}

template<class K, class V>
Collection<K> Dictionary<K, V>::Keys()
{
	Collection<K> res;
	for (int i=0; i<numEntries; i++) res.Add(entries[i]->Key);
	return res;
}

template<class K, class V>
Collection<V> Dictionary<K, V>::Values()
{
	Collection<V> res;
	for (int i=0; i<numEntries; i++) res.Add(entries[i]->Value);
	return res;
}
 
#endif // DICTIONARY_H
