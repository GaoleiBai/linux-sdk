#ifndef NOBJECTDICTIONARY_H
#define NOBJECTDICTIONARY_H

#include "dictionary.h"
#include "../n_object.h"

class NObjectDictionary : public Dictionary<NObject *, NObject *>, public NObject {

public:
	NObjectDictionary();
	virtual ~NObjectDictionary();
	
	virtual void SetKey(NObject *key, NObject *value);
	virtual NObject *operator[](const NObject *key);
	
	virtual Text ToText();
	virtual void Serialize(const Serializator &s);
	virtual NObject *Deserialize(const Serializator &s);

protected:
	static int compare(const void *u, const void *v);

};

#endif // NOBJECTDICTIONARY_H
