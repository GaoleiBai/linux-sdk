#ifndef BINARYFORMATTER_H
#define BINARYFORMATTER_H

#include "../n_object.h"
#include "ifile.h"
#include "iserializable.h"

class BinaryFormatter : public NObject {

public:
	BinaryFormatter(const IFile &file);
	virtual ~BinaryFormatter();

	ISerializable & Get();
	void Put(const ISerializable &o);

};

#endif // BINARYFORMATTER_H
