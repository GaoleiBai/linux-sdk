#ifndef HELPCLASS_H
#define HELPCLASS_H

#include "../../LFC/LFC.h"

class HelpClass : public NObject {

public:
	HelpClass();
	virtual ~HelpClass();
	
	virtual NObject *NewInstance();
	virtual void Serialize(const Serializator &s);
	virtual NObject *Deserialize(const Serializator &s);
	
private:
	char nchar;
	short nshort;
	int nint;
	long nlong;
	long long nlonglong;
	unsigned char nuchar;
	unsigned short nushort;
	unsigned int nuint;
	unsigned long nulong;
	unsigned long long nulonglong;
	float nfloat;
	double ndouble;
	long double nlongdouble;
	Text *atext;
	DateTime *adatetime;
	NObjectCollection *nobjectcollection;
	NObjectDictionary *nobjectdictionary;
	Buffer *abuffer;
	TextBuffer *atextbuffer;
	
};

#endif // HELPCLASS_H
