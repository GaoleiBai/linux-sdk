#include "exception.h"
#include "LFC.h"

Exception::Exception()
{
	t = new Text("");
}

Exception::Exception(const char *p)
{
	t = new Text(p);
}

Exception::Exception(const Text &p)
{
	t = new Text(p);
}

Exception::~Exception()
{
	delete t;
}

