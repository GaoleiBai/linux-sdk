#include "nwchar.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <wchar.h>
#include <errno.h>
#include <stdio.h>

NWChar::NWChar()
{
	value = 0;
}

NWChar::NWChar(wchar_t c)
{
	value = c;
}

NWChar::NWChar(const NWChar &c)
{
	value = c.value;
}

NWChar::~NWChar()
{
}

wchar_t NWChar::MaxValue()
{
	return WCHAR_MAX;
}

wchar_t NWChar::MinValue()
{
	return WCHAR_MAX;
}

wchar_t NWChar::Parse(const Text &t)
{
	wchar_t v = 0;
	if (!TryParse(t, v))
		throw new Exception("Number out limits", __FILE__, __LINE__, __func__);
}

bool NWChar::TryParse(const Text &t, wchar_t &c)
{
	char cadena[1001];
	((Text *)&t)->GetAnsiString(cadena, 1000);
	errno = 0;
	long long ll = atoll(cadena);
	if (errno != 0) return false;
	if (ll < MinValue() || ll > MaxValue()) return false;
	c = ll;
	return true;
}

Text NWChar::ToText(const Text &format)
{
	char cadena[1001];
	((Text *)&format)->GetAnsiString(cadena, 1000);
	
	char res[1001];
	sprintf(res, cadena, value);
	return (Text)cadena;
}

wchar_t &NWChar::Value()
{
	return value;
}

NObject *NWChar::NewInstance()
{
	return new NWChar();
}

Text NWChar::ToText()
{
	const wchar_t cadena[] = { value, 0 };
	return (Text)cadena;
}

int NWChar::Compare(const NObject &o)
{
	long long vo = ((NObject *)&o)->ToLongLong();
	if (value > vo) return 1;
	else if (value < vo) return -1;
	else return 0;
}

void NWChar::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put((short)value);
}

void NWChar::Deserialize(const Serializator &s)
{
	value = (short)((Serializator *)&s)->GetShort();
}
