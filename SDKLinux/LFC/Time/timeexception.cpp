#include "timeexception.h"

TimeException::TimeException() : Exception()
{
}

TimeException::TimeException(const Text &t, const char *file, int line, const char *func) : Exception(t, file, line, func)
{
	
}

TimeException::~TimeException()
{
}

