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
		Text fileToTest = "/var/log/dpkg.log";
		
		if (!File::Exists(fileToTest)) {
			StdOut::PrintLine("No se puede acceder al fichero de pruebas.");
			return -1;
		}
		
		try { File::Copy(fileToTest, "prueba"); }
		catch (FileSystemException * e) {
			StdOut::PrintLine("File copy didn't work");
			delete e;
			return -1;
		}
		
		Text f1 = File::ReadAllText(fileToTest);
		Text f2 = File::ReadAllText("prueba");
		if (f1 != f2) {
			StdOut::PrintLine("File copy is not exact");
			return -1;
		}
		
		Buffer b1 = File::ReadAllBytes(fileToTest);
		Buffer b2 = File::ReadAllBytes("prueba");
		if (b1 != b2) {
			StdOut::PrintLine("File copy is not exact");
			return -1;
		}
		
		if (b1.ToText() != f2) {
			StdOut::PrintLine("Buffer and text don't match");
			return -1;
		}
		
		File::WriteAllBytes("prueba2", b1);
		Buffer b3 = File::ReadAllBytes("prueba2");
		if (b3 != b1) {
			StdOut::PrintLine("WriteAllBytes didn't work");
			return -1;
		}
		
		File::Move("prueba2", "prueba3");
		Buffer b4 = File::ReadAllBytes("prueba3");
		if (b1 != b4) {
			StdOut::PrintLine("Move didn't work");
			return -1;
		}
		
		Collection<Text *> lines = File::ReadAllLines(fileToTest);
		
		//for (int i=0; i<lines.Count(); i++)
		//	StdOut::PrintLine(lines[i]);

		Text t = Text::Join(lines, "\n");
		Text u = File::ReadAllText(fileToTest);
		
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
