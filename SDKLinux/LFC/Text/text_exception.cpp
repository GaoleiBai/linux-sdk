#include "text_exception.h"
#include "../LFC.h"

TextException::TextException() : Exception("TextException")
{
	
}

TextException::TextException(const char *t) : Exception(t)
{
	
}

TextException::TextException(const Text &t) : Exception(t)
{
	
}

TextException::TextException(const TextException &e) : Exception(e.t)
{

}

TextException::~TextException()
{
}

