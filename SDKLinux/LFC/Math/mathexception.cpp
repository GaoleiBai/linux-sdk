#include "mathexception.h"

MathException::MathException() : 
	Exception()
{
}

MathException::MathException(const Text &t, const char *file, int line, const char *func) : 
	Exception(t, file, line, func)
{	
}

MathException::~MathException()
{
}

