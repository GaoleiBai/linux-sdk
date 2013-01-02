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
