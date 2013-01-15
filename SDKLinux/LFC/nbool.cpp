#include "nbool.h"
#include "exception.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <typeinfo>

NBool::NBool()
{
	value = false;
}

NBool::NBool(bool b)
{
	value = b;
}

NBool::~NBool()
{
}

bool NBool::Parse(const Text &text)
{
	bool b = false;
	if (!TryParse(text, b))
		throw new Exception("Not bool found", __FILE__, __LINE__, __func__);
	return b;
}

bool NBool::TryParse(const Text &text, bool &b)
{
	if (*((Text *)&text) == "true") b = true;
	else if (*((Text *)&text) == "false") b = false;
	else return false;
	return true;
}

bool &NBool::Value()
{
	return value;
}

NObject *NBool::NewInstance()
{
	return new NBool();
}

Text NBool::ToText()
{
	return value ? (Text)"true" : (Text)"false";
}

int NBool::Compare(const NObject &o)
{
	if (typeid(*this) == typeid(o)){
		if (value == ((NBool *)&o)->value) return 0;
		else if (value) return 1;
		else return 0;
	}
	return NObject::Compare(o);
}

void NBool::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NBool::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetBool();
}