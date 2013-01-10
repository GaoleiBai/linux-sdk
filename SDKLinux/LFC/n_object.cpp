#include <typeinfo>
#include "n_object.h"
#include "Text/text.h"

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

void NObject::Serialize(const IFile &file)
{
	
}

NObject NObject::Deserialize(const IFile &file)
{
	
}