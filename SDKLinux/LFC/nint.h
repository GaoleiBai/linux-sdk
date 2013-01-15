#ifndef NINT_H
#define NINT_H

#include "n_object.h"

class Text;

class NInt : public NObject {

public:
	NInt();
	NInt(int n);
	virtual ~NInt();

	static int MaxValue();
	static int MinValue();
	static int Parse(const Text &text);
	static bool TryParse(const Text &text, int &n);
	Text ToText(const Text &format);
	
	int &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
protected:
	int value;
	
};

#endif // NINT_H
