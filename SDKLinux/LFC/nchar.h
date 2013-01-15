#ifndef NCHAR_H
#define NCHAR_H

#include "n_object.h"

class Text;

class NChar : public NObject {

public:
	NChar();
	NChar(char c);
	virtual ~NChar();

	static char MaxValue();
	static char MinValue();
	static char Parse(const Text &text);
	static bool TryParse(const Text &text, char &c);
	Text ToText(const Text &format);
	
	char &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
protected:
	char value;
	
};

#endif // NCHAR_H
