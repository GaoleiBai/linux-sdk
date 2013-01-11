#ifndef NOBJECTDICTIONARY_H
#define NOBJECTDICTIONARY_H

#include "dictionary.h"
#include "../n_object.h"

class NObjectDictionary : public Dictionary<NObject *, NObject *>, public NObject {

public:
	NObjectDictionary();
	virtual ~NObjectDictionary();
	
	virtual Text ToText();

protected:
	static int compare(const void *u, const void *v);

};

#endif // NOBJECTDICTIONARY_H
