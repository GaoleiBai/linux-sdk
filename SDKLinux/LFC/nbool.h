#ifndef NBOOL_H
#define NBOOL_H

#include "n_object.h"

class Text;

class NBool : public NObject {

public:
	NBool();
	NBool(bool b);
	virtual ~NBool();

	static bool Parse(const Text &text);
	static bool TryParse(const Text &text, bool &b);
	
	bool &Value();
	
	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
protected:
	bool value;
	
};

#endif // NBOOL_H
