#include "nchar.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <typeinfo>
#include <stdio.h>

NChar::NChar()
{
	value = 0;
}

NChar::NChar(char c)
{
	value = c;
}

NChar::~NChar()
{
}

char NChar::MaxValue() 
{
	return SCHAR_MAX;
}

char NChar::MinValue()
{
	return SCHAR_MIN;
}

char NChar::Parse(const Text &text)
{
	char c = 0;
	if (!TryParse(text, c))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return c;
}

bool NChar::TryParse(const Text &text, char &c)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	long long l = atoll(cadena);
	if (l > MaxValue() || l < MinValue()) return false;
	c = l;
	return true;
}

Text NChar::ToText(const Text &format)
{
	char cadena[1001];
	((Text *)&format)->GetAnsiString(cadena, 1000);
	
	char res[1001];
	sprintf(res, cadena, value);
	return (Text)res;
}

char &NChar::Value()
{
	return value;
}

NObject *NChar::NewInstance()
{
	return new NChar();
}

Text NChar::ToText()
{
	const char cadena[] = { value, 0 };
	return (Text)cadena;
}

int NChar::Compare(const NObject &o)
{
	if (typeid(*this) == typeid(o)) 
		return this->value - ((NChar *)&o)->value;
	return NObject::Compare(o);
}

void NChar::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NChar::Deserialize(const Serializator &s)
{
	((Serializator *)&s)->GetChar();
}