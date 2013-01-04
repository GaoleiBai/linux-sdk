#include "stdout.h"
#include "stdio.h"

StdOut::StdOut()
{
}

StdOut::~StdOut()
{
}

void StdOut::Print(const Text &t)
{
	printf("%S", t.p);
}

void StdOut::PrintLine(const Text &t)
{
	printf("%S\r\n", t.p);
}

void StdOut::PrintLine()
{
	printf("\r\n");
}