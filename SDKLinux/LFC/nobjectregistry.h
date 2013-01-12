#ifndef NOBJECTREGISTRY_H
#define NOBJECTREGISTRY_H

#include "Collections/dictionary.h"

class NObjectRegistry {

public:
	NObjectRegistry();
	virtual ~NObjectRegistry();
	
	static void Register(const NObject &o);
	static NObject *GetInstance(const Text &classname);

private:
	Dictionary<Text *, NObject *> *classes;
	static NObjectRegistry *registry;

};

#endif // NOBJECTREGISTRY_H
