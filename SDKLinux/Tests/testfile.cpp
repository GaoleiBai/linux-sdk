#include "../LFC/LFC.h"
#include "testfile.h"

TestFile::TestFile()
{
}

TestFile::~TestFile()
{
}

int TestFile::Perform()
{
	try {
		if (!File::Exists("/var/log/kern.log.1")) {
			StdOut::PrintLine("No se puede acceder al fichero de pruebas.");
			return -1;
		}
		
		try { File::Copy("/var/log/kern.log.1", "prueba"); }
		catch (FileSystemException * e) {
			StdOut::PrintLine("File copy didn't work");
			delete e;
			return -1;
		}
		
		Text f1 = File::ReadAllText("/var/log/kern.log.1");
		Text f2 = File::ReadAllText("prueba");
		if (f1 != f2) {
			StdOut::PrintLine("File copy is not exact");
			return -1;
		}
		
		Buffer b1 = File::ReadAllBytes("/var/log/kern.log.1");
		Buffer b2 = File::ReadAllBytes("prueba");
		if (b1 != b2) {
			StdOut::PrintLine("File copy is not exact");
			return -1;
		}
		
		Collection<Text *> lines = File::ReadAllLines("/var/log/kern.log.1");
		
		for (int i=0; i<lines.Count(); i++)
			StdOut::PrintLine(lines[i]);

		Text t = Text::Join(lines, "\n");
		Text u = File::ReadAllText("/var/log/kern.log.1");
		
		if (t != u) {
			StdOut::PrintLine("Diferent results between ReadAllLines and ReadAllText");
			return -1;
		}
		
		lines.DeleteAndClear();
	} catch (Exception *e) {
		delete e;
		return -1;
	}
	
	return 0;
}
