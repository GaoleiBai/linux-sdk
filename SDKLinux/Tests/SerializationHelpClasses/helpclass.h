#ifndef HELPCLASS_H
#define HELPCLASS_H

#include "../../LFC/LFC.h"

class HelpClass {

public:
	HelpClass();
	virtual ~HelpClass();
	
	virtual void Serialize(const Serializator &s);
	virtual NObject *Deserialize(const Serializator &s);
	
private:
	char nchar;
	int nint;

};

#endif // HELPCLASS_H
