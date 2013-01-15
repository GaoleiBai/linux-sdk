#include "nint.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>

NInt::NInt()
{
	value = 0;
}

NInt::NInt(int n)
{
	value = n;
}

NInt::~NInt()
{
}

int NInt::MaxValue()
{
	return INT_MAX;
}

int NInt::MinValue()
{
	return INT_MIN;
}

int &NInt::Value()
{
	return value;
}

int NInt::Parse(const Text &text)
{
	int n = 0;
	if (!TryParse(text, n))
		throw new Exception("Number out of limits", __FILE__, __LINE__, __func__);
	return n;
}

bool NInt::TryParse(const Text &text, int &n)
{
	char cadena[1001];
	((Text *)&text)->GetAnsiString(cadena, 1000);
	
	long long ll = atoll(cadena);
	if (ll > MaxValue() || ll < MinValue()) return false;
	n = ll;
	return true;
}

Text NInt::ToText(const Text &format)
{
	char ff[1001];
	((Text *)&format)->GetAnsiString(ff, 1000);
	
	char tt[1001];
	sprintf(tt, ff, value);
	return (Text)tt;
}

NObject *NInt::NewInstance()
{
	return new NInt();
}

Text NInt::ToText()
{
	char cadena[1001];
	sprintf(cadena, "%d", value);
	return (Text)cadena;
}

int NInt::Compare(const NObject &o)
{
	if (typeid(*this) == typeid(o))
		return this->value - ((NInt *)&o)->value;
	return NObject::Compare(o);
}

void NInt::Serialize(const Serializator &s) 
{
	((Serializator *)&s)->Put(value);
}

void NInt::Deserialize(const Serializator &s) 
{
	value = ((Serializator *)&s)->GetInt();
}

