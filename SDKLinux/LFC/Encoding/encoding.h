#ifndef ENCODING_H
#define ENCODING_H

class Text;

class Encoding {

public:
	Encoding();
	virtual ~Encoding();

	static void SetLocale(Text &locale);
	static void SetLocale(char *locale);
	static void SetLocale(wchar_t *locale);

};

#endif // ENCODING_H
