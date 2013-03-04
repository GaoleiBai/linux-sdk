#ifndef NWCHAR_H
#define NWCHAR_H

#include "n_object.h"

class Text;

class NWChar : public NObject {

public:
	NWChar();
	NWChar(wchar_t c);
	NWChar(const NWChar &c);
	virtual ~NWChar();
	
	static wchar_t MaxValue();
	static wchar_t MinValue();
	static wchar_t Parse(const Text &t);
	static bool TryParse(const Text &t, wchar_t &c);
	Text ToText(const Text &format);
	
	wchar_t &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	virtual long long ToLongLong();
	virtual long double ToLongDouble();
	
	static int COMPARER(const void *u, const void *v);
	
	bool IsAlpha(wchar_t c);
	bool IsAlphaNumeric(wchar_t c);
	bool IsAscii(wchar_t c);
	bool IsControl(wchar_t c);
	bool IsDigit(wchar_t c);
	bool IsGraph(wchar_t c);
	bool IsLower(wchar_t c);
	bool IsPrintable(wchar_t c);
	bool IsPunctuation(wchar_t c);
	bool IsSpace(wchar_t c);
	bool IsUpper(wchar_t c);
	bool IsXDigit(wchar_t c);

protected:
	wchar_t value;

};

#endif // NWCHAR_H
