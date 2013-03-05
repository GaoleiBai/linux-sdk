#include "nwchar.h"
#include "Text/text.h"
#include "FileSystem/serializator.h"
#include <limits.h>
#include <wchar.h>
#include <errno.h>
#include <stdio.h>
#include <wctype.h>

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

int NWChar::Compare(const NWChar &c)
{
	if (value > c.value) return 1;
	else if (value < c.value) return -1;
	else return 0;
}

void NWChar::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(value);
}

void NWChar::Deserialize(const Serializator &s)
{
	value = (short)((Serializator *)&s)->GetWChar();
}

long long NWChar::ToLongLong()
{
	return value;
}

long double NWChar::ToLongDouble()
{
	return value;
}

int NWChar::COMPARER(const void *u, const void *v)
{
	wchar_t *uu = (wchar_t *)u;
	wchar_t *vv = (wchar_t *)v;
	if (*uu > *vv) return 1;
	else if (*uu < *vv) return -1;
	else return 0;
}

bool NWChar::IsAlpha(wchar_t c)
{
	return iswalpha(c);
}

bool NWChar::IsAlphaNumeric(wchar_t c)
{
	return iswalnum(c);
}

bool NWChar::IsBlank(wchar_t c)
{
	return iswblank(c);
}

bool NWChar::IsControl(wchar_t c)
{
	return iswcntrl(c);
}

bool NWChar::IsDigit(wchar_t c)
{
	return iswdigit(c);
}

bool NWChar::IsGraph(wchar_t c)
{
	return iswgraph(c);
}

bool NWChar::IsLower(wchar_t c)
{
	return iswlower(c);
}

bool NWChar::IsPrintable(wchar_t c)
{
	return iswprint(c);
}

bool NWChar::IsPunctuation(wchar_t c)
{
	return iswpunct(c);
}

bool NWChar::IsSpace(wchar_t c)
{
	return iswspace(c);
}

bool NWChar::IsUpper(wchar_t c)
{
	return iswupper(c);
}

bool NWChar::IsXDigit(wchar_t c)
{
	return iswxdigit(c);
}
