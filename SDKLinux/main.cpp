#include <stdio.h>
#include "./LFC/LFC.h"
#include "./Tests/Tests.h";
#include "LFC/Collections/collection.h"

int main(int argc, char **argv)
{
	lfc_init(); // lfc initialization
	
	printf("hello world\n");
	
	if (TestText::PerformAnsi() != 0) {
		printf("PerformAnsi error!");
		return -1;
	}
	if (TestText::PerformWide() != 0) {
		printf("PerformWide error!");
		return -1;
	}
	
	return 0;
}
