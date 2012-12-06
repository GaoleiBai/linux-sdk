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

Exception::Exception(const Exception &e)
{
	t = new Text(*e.t);
}

Exception::~Exception()
{
	delete t;
}

Text Exception::ToText()
{
	return Text(*t);
}

