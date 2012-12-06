#include <stdio.h>
#include "./LFC/LFC.h"
#include "./Tests/Tests.h"
#include "LFC/Collections/collection.h"

int main(int argc, char **argv)
{
	lfc_init(); // lfc initialization
	
	printf("hello world\n");
	
	if (TestText::PerformAnsi() != 0) {
		printf("PerformAnsi error!\r\n");
		return -1;
	}
	if (TestText::PerformWide() != 0) {
		printf("PerformWide error!\r\n");
		return -1;
	}
	if (TestDirectory::Perform() != 0) {
		printf("TestDirectory::Perform error!\r\n");
		return -1;
	}
	
	return 0;
}
