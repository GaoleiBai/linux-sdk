#include "dataexception.h"

DataException::DataException() : Exception()
{
}

DataException::DataException(const Text &description, const char *file, int line, const char *func)
	: Exception(description, file, line, func)
{
}

DataException::~DataException()
{
}

