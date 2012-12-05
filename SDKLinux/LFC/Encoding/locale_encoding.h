#ifndef LOCALE_ENCODING_H
#define LOCALE_ENCODING_H

#include "../n_object.h"

class Text;

class Locale : NObject {

public:
	Locale();
	virtual ~Locale();

	static void SetLocale(Text &locale);
	static void SetLocale(const char *locale);
	static void SetLocale(const wchar_t *locale);
};

#endif // LOCALE_H
