#include "collection_exception.h"

CollectionException::CollectionException() : Exception()
{
}

CollectionException::CollectionException(const Text &t, const char *file, int line, const char *func) : Exception(t, file, line, func)
{
	
}

CollectionException::~CollectionException()
{
}

