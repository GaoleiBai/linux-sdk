#include <stdio.h>
#include "./LFC/LFC.h"
#include "./Tests/Tests.h";
#include "LFC/Collections/collection.h"

int main(int argc, char **argv)
{
	printf("hello world\n");
	
	if (TestText::Perform() != 0) {
		printf("TestText error!");
		return -1;
	}
	
	return 0;
}
