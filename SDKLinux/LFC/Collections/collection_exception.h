#ifndef COLLECTIONEXCEPTION_H
#define COLLECTIONEXCEPTION_H

#include "../exception.h"

class CollectionException : Exception {

public:
	CollectionException();
	CollectionException(const char *t);
	CollectionException(const Text &t);
	virtual ~CollectionException();

};

#endif // COLLECTIONEXCEPTION_H
