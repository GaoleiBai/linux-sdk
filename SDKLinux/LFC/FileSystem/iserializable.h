#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include "ifile.h"

class ISerializable {

public:
	ISerializable();
	virtual ~ISerializable();
	
	virtual void Serialize(const IFile &file) = 0;
	virtual ISerializable &Deserialize(const IFile &file) = 0;

};

#endif // ISERIALIZABLE_H
