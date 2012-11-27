#include "collection_exception.h"

CollectionException::CollectionException() : Exception()
{
}

CollectionException::CollectionException(const char *t) : Exception(t)
{
	
}

CollectionException::CollectionException(const Text &t) : Exception(t)
{
	
}

CollectionException::~CollectionException()
{
}

