#include "encoding.h"
#include "../Text/text.h"
#include <locale.h>

Encoding::Encoding()
{
}

Encoding::~Encoding()
{
}

void Encoding::SetLocale(Text &locale)
{
	setlocale(LC_ALL, "C");
	int len = locale.length;
	char *loc = new char[locale.length + 1];
	locale.GetAnsiString(loc, len);
	setlocale(LC_ALL, loc);
	delete loc;
}

void Encoding::SetLocale(char *locale)
{
	setlocale(LC_ALL, locale);	
}

void Encoding::SetLocale(wchar_t *locale)
{
	Text loc(locale);
	SetLocale(loc);
}

