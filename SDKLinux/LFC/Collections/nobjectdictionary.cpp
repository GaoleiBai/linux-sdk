#include "nobjectdictionary.h"
#include "../Text/text_buffer.h"

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

