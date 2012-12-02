#include <locale.h>
#include "../Text/text.h"
#include "./locale_encoding.h"

Locale::Locale()
{
}

Locale::~Locale()
{
}

void Locale::SetLocale(Text &locale)
{
	setlocale(LC_ALL, "C");
	int len = locale.length;
	char *loc = new char[locale.length + 1];
	locale.GetAnsiString(loc, len);
	setlocale(LC_ALL, loc);
	delete loc;
}

void Locale::SetLocale(const char *locale)
{
	setlocale(LC_ALL, locale);	
}

void Locale::SetLocale(const wchar_t *locale)
{
	Text loc(locale);
	SetLocale(loc);
}

