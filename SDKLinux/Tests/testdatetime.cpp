#include "testdatetime.h"
#include "../LFC/LFC.h"
#include <stdio.h>

TestDateTime::TestDateTime()
{
}

TestDateTime::~TestDateTime()
{
}

int TestDateTime::Perform()
{
	DateTime t;
	t.ToText().Print();
	printf("\r\n");
	
	t.ToUtcDateTime().ToText().Print();
	printf("\r\n");

	return 0;
}

