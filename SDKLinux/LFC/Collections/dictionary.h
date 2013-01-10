#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "collection.h"
#include "collection_exception.h"
#include "../n_object.h"
#include <stdlib.h>

template<class K, class V>
class DictionaryEntry {
public:
	K Key;
	V Value;
	
	DictionaryEntry(K key, V value);
	~DictionaryEntry();
	
};

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
class Dictionary : public NObject {

public:
	Dictionary(int (*COMPARER)(const void *u, const void *v));
	virtual ~Dictionary();
	
	void SetKey(K key, V value);
	bool GetKey(K key, V &value);
	void ClearKey(K key);
	bool ExistsKet(K key);
	void Clear();
	void Pack();

	Collection<K> Keys();
	Collection<V> Values();
	
private:
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
Dictionary<K, V>::Dictionary(int (*COMPARER)(const void *u, const void *v))
{
	capacity = 0;
	numEntries = 0;
	KEY_COMPARER = COMPARER;
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
	delete entries;
	entries = q;
	this->capacity = newCapacity;
}

template<class K, class V>
int Dictionary<K, V>::binarySearchIx(K key)
{
	DictionaryEntry<K, V> *e = new DictionaryEntry<K, V>[1];
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
	keys[0] = **uu.Key;
	keys[1] = **vv.Key;
	return KEY_COMPARER((const void *)&keys, (const void *)&(keys + 1));
}

template<class K, class V>
void Dictionary<K, V>::SetKey(K key, V value)
{
	int ix = binarySearchIx(key);
	if (ix != -1) {
		entries[ix]->Value = value;
	} else {
		// Create and insert the new entry
		DictionaryEntry<K, V> *e = new DictionaryEntry<K, V>(key, value);
		ix = numEntries;
		for (int i=numEntries-1; i>=0; i--) {
			if (KEY_COMPARER(&key, &entries[i].Key) > 0) break;
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
	value = entries[ix].Value;
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
bool Dictionary<K, V>::ExistsKet(K key)
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
	DictionaryEntry<K, V> **q = new DictionaryEntry<K, V> *[numEntries];
	for (int i=0; i<numEntries; i++) q[i] = entries[i];
	capacity = numEntries;
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
