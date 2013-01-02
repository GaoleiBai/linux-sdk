#include "text_exception.h"
#include "../LFC.h"

TextException::TextException() : Exception()
{
	
}

TextException::TextException(const char *t, const char *file, int line, const char *func) : Exception(t, file, line, func)
{
	
}

TextException::TextException(const Text &t, const char *file, int line, const char *func) : Exception(t, file, line, func)
{
	
}

TextException::~TextException()
{
}

