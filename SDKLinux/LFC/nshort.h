#ifndef NSHORT_H
#define NSHORT_H

#include "n_object.h"

class NShort : public NObject {

public:
	NShort();
	NShort(short s);
	virtual ~NShort();
	
	static short MaxValue();
	static short MinValue();
	static short Parse(const Text &text);
	static bool TryParse(const Text &text, short &c);
	Text ToText(const Text &format);
	
	short &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
protected:
	short value;
	

};

#endif // NSHORT_H
