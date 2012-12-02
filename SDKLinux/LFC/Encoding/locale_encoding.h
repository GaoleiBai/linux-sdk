#ifndef LOCALE_ENCODING_H
#define LOCALE_ENCODING_H

class Text;

class Locale {

public:
	Locale();
	virtual ~Locale();

	void SetLocale(Text &locale);
	void SetLocale(const char *locale);
	void SetLocale(const wchar_t *locale);
};

#endif // LOCALE_H
