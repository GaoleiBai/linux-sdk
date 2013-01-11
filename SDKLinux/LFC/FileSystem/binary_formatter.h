#ifndef BINARYFORMATTER_H
#define BINARYFORMATTER_H

#include "../n_object.h"
#include "ifile.h"
#include "iserializable.h"

class BinaryFormatter : public NObject {

public:
	BinaryFormatter(const IFile &file);
	virtual ~BinaryFormatter();

	NObject Get();
	void Put(const NObject &o);

};

#endif // BINARYFORMATTER_H
