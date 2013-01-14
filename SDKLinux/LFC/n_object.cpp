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

NObject *NObject::NewInstance()
{
	throw new Exception((Text)typeid(*this).name() + "::NewInstance() needs to be implemented to be able to deserializate a class.", __FILE__, __LINE__, __func__);
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
	throw new Exception((Text)typeid(*this).name() + "::Serialize() must be able to serialize.", __FILE__, __LINE__, __func__);
}

NObject *NObject::Deserialize(const Serializator &s)
{
	throw new Exception((Text)typeid(*this).name() + "Deserialize() must be implemented to be able to deserialize.", __FILE__, __LINE__, __func__);
}