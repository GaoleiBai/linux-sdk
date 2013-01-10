#include <stdio.h>
#include "./LFC/LFC.h"
#include "./Tests/Tests.h"

int main(int argc, char **argv)
{
	lfc_init(); // lfc initialization
	
	StdOut::PrintLine("hello world");
	
	if (TestText::PerformAnsi() != 0) {
		StdOut::PrintLine("PerformAnsi error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestText::PerformWide() != 0) {
		StdOut::PrintLine("PerformWide error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestDirectory::Perform() != 0) {
		StdOut::PrintLine("TestDirectory::Perform error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestDateTime::Perform() != 0) {
		StdOut::PrintLine("TestDateTime::Perform error!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestAdministration::Perform() != 0) {
		StdOut::PrintLine("TestAdministration::Perform error!!!");
		return -1;
	}
	StdOut::PrintLine();
	
	if (TestFile::Perform() != 0) {
		StdOut::PrintLine("TestFile::Perform error!!!");
		return -1;
	}
	
	if (TestCollection::Perform() != 0) {
		StdOut::PrintLine("TestCollection::Perform error!!!");
		return -1;
	}
	
	if (TestDictionary::Perform() != 0) {
		StdOut::PrintLine("TestDictionary::Perform error!!!");
		return -1;
	}
	
	return 0;
}
