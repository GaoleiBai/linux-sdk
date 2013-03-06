#ifndef DATAEXCEPTION_H
#define DATAEXCEPTION_H

#include "../exception.h"

class DataException : public Exception {

public:
	DataException();
	DataException(const Text &description, const char *file, int line, const char *func);
	virtual ~DataException();

};

#endif // DATAEXCEPTION_H
