#include <typeinfo>
#include "n_object.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"

NObject::NObject()
{
}

NObject::~NObject()
{
}

Text NObject::ToText()
{
	return Text(typeid(*this).name());
}

int NObject::Compare(const NObject &o)
{
	return ToText().Compare(((NObject *)&o)->ToText());	
}

void NObject::Serialize(const Serializator &s)
{
	throw new Exception((Text)"Serialize() must be implemented in " + typeid(*this).name() + " to allow being serialized.", __FILE__, __LINE__, __func__);
}

NObject *NObject::Deserialize(const Serializator &s)
{
	throw new Exception((Text)"Deserialize() must be implemented in " + typeid(*this).name() + " to allow being serialized.", __FILE__, __LINE__, __func__);
}