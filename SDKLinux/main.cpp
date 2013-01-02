#include <stdio.h>
#include "./LFC/LFC.h"
#include "./Tests/Tests.h"

int main(int argc, char **argv)
{
	lfc_init(); // lfc initialization
	
	StdOut::PrintLine("hello world");
	
	if (TestText::PerformAnsi() != 0) {
		printf("PerformAnsi error!\r\n");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestText::PerformWide() != 0) {
		printf("PerformWide error!\r\n");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestDirectory::Perform() != 0) {
		printf("TestDirectory::Perform error!\r\n");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestDateTime::Perform() != 0) {
		printf("TestDateTime::Perform error!\r\n");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestAdministration::Perform() != 0) {
		StdOut::PrintLine("TestAdministration::Perform error!!!");
		return -1;
	}
	
	return 0;
}
