#include "timeexception.h"
#include "../exception.h"

TimeException::TimeException() : Exception()
{
}

TimeException::TimeException(const char *t) : Exception(t)
{
	
}

TimeException::TimeException(const Text &t) : Exception(t)
{
	
}

TimeException::TimeException(const TimeException &t) : Exception(t)
{

}

TimeException::~TimeException()
{
}

