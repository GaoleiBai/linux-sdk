#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../n_object.h"
#include <stdlib.h>

template<class K, class V>
class DictionaryEntry {
public:
	K Key;
	V Value;
	
	DictionaryEntry(K key, V value);
	
};

template<class K, class V>
DictionaryEntry<K, V>::DictionaryEntry(K key, V value)
{
	this->key = key;
	this->value = value;
}

template<class K, class V>
class Dictionary : public NObject {

public:
	Dictionary(int (*COMPARER)(const void *u, const void *v));
	virtual ~Dictionary();
	
	void SetEntry(K key, V value);
	void DeleteEntry(K key);
	
	V &operator[](K key);
	
private:
	DictionaryEntry<K, V> *entries;
	int numEntries;
	int capacity;
	bool isSorted;
	static int (*KEY_COMPARER)(const void *u, const void *v);
	
	void ensureCapacity(int capacity);
	void qsort();
	int binarySearchIx(K key);
	static int ENTRY_COMPARER(const void *u, const void *v);

};

template<class K, class V>
Dictionary<K, V>::Dictionary(int (*COMPARER)(const void *u, const void *v))
{
	capacity = 0;
	numEntries = 0;
	isSorted = false;
	KEY_COMPARER = COMPARER;
	ensureCapacity(1000);
}

template<class K, class V>
Dictionary<K, V>::~Dictionary()
{
	delete entries;
}

template<class K, class V>
void Dictionary<K, V>::ensureCapacity(int capacity)
{
	if (this->capacity >= capacity) return;
	
	int newCapacity = capacity + 1000;
	DictionaryEntry<K, V> *q = new DictionaryEntry<K, V>[newCapacity];
	for (int i=0; i<numEntries; i++)
		q[i] = entries[i];
	delete entries;
	entries = q;
	this->capacity = newCapacity;
}

template<class K, class V>
void Dictionary<K, V>::qsort()
{
	if (isSorted) return;
	::qsort(entries, numEntries, sizeof(entries[0]), ENTRY_COMPARER);
	isSorted = true;
}

template<class K, class V>
int Dictionary<K, V>::binarySearchIx(K key)
{
	qsort();
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
void Dictionary<K, V>::SetEntry(K key, V value)
{
	int ix = binarySearchIx(key);
	if (ix != -1) {
		entries[ix]->Value = value;
	} else {
		aaa
		ensureCapacity(numEntries + 1);
		entries[numEntries++] = new DictionaryEntry<K, V>(key, value);
		isSorted = false;
	}
}

template<class K, class V>
void Dictionary<K, V>::DeleteEntry(K key)
{
	int ix = binarySearchIx(key);
	if (ix == -1) return;
	numEntries--;
	for (int i=ix; i<numEntries; i++)
		entries[i] = entries[i + 1];
}

#endif // DICTIONARY_H
