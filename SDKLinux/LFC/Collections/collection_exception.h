#ifndef COLLECTIONEXCEPTION_H
#define COLLECTIONEXCEPTION_H

#include "../exception.h"

class CollectionException : public Exception {

public:
	CollectionException();
	CollectionException(const Text &t, const char *file, int line, const char *func);
	virtual ~CollectionException();

};

#endif // COLLECTIONEXCEPTION_H
