#include "nobjectdictionary.h"

NObjectDictionary::NObjectDictionary() : Dictionary<NObject *, NObject *>(compare), NObject()
{
}

NObjectDictionary::~NObjectDictionary()
{
}

int NObjectDictionary::compare(const void *u, const void *v)
{
	NObject **uu = (NObject **)u;
	NObject **vv = (NObject **)v;
	return (*uu)->Compare(**vv);
}

