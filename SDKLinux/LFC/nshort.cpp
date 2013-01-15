#include "nshort.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdio.h>
#include <typeinfo>

NShort::NShort()
{
	value = 0;
}

NShort::NShort(short s)
{
	value = s;
}

NShort::~NShort()
{
}

short NShort::MaxValue()
{
	return SHRT_MAX;
}

short NShort::MinValue()
{
	return SHRT_MIN;
}

short NShort::Parse(const Text &text)
{
	short s = 0;
	if (!TryParse(text, s))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return s;
}

bool NShort::TryParse(const Text &text, short &c)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	long long ll = atoll(cadena);
	if (ll > MaxValue() || ll < MinValue()) return false;
	c = ll;
	return true;
}

Text NShort::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char ss[1001];
	sprintf(ss, ff, value);
	return (Text)ss;
}

short &NShort::Value()
{
	return value;
}

NObject *NShort::NewInstance()
{
	return new NShort();
}

Text NShort::ToText()
{
	char cadena[100];
	sprintf(cadena, "%hd", value);
	return (Text)cadena;
}

int NShort::Compare(const NObject &o)
{
	if (typeid(*this) == typeid(o))
		return value - ((NShort *)&o)->value;
	return NObject::Compare(o);
}

void NShort::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NShort::Deserialize(const Serializator &s)
{
	value = ((Serializator *)&s)->GetShort();
}


