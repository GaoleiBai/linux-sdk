#include "nobjectdictionary.h"
#include "../Text/text_buffer.h"
#include "../FileSystem/serializator.h"

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

Text NObjectDictionary::ToText()
{
	TextBuffer b;
	for (int i=0; i<numEntries; i++) 
		b.AppendLine(entries[i]->Key->ToText() + ":" + entries[i]->Value->ToText());
	return b.ToText();
}

void NObjectDictionary::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(numEntries);
	for (int i=0; i<numEntries; i++) {
		((Serializator *)&s)->Put(*(entries[i]->Key));
		((Serializator *)&s)->Put(*(entries[i]->Value));
	}
}

NObject *NObjectDictionary::Deserialize(const Serializator &s)
{
	
}

NObject *NObjectDictionary::operator [](const NObject *key)
{
	NObject *value = NULL;
	if (!GetKey((NObject *)key, value)) return NULL;
	return value;
}

void NObjectDictionary::SetKey(NObject *key, NObject *value)
{
	if (key == NULL)
		throw new CollectionException("No NULL keys are allowed.", __FILE__, __LINE__, __func__);
	if (value == NULL)
		throw new CollectionException("No NULL values are allowed.", __FILE__, __LINE__, __func__);
		
	Dictionary<NObject *, NObject *>::SetKey(key, value);
}

