#include "testserialization.h"
#include "SerializationHelpClasses/helpclass.h"

TestSerialization::TestSerialization()
{
}

TestSerialization::~TestSerialization()
{
}

int TestSerialization::Perform()
{
	try {
		Text t("Hola mundo");
		HelpClass h;
		NObjectRegistry::Register(h);
		
		Buffer b;
		Serializator s(b);
		s.Put(t);
		
		b.FSetStart();
		Text *tt = (Text *)s.GetNObject();
		delete tt;
		
		b.FSetStart();
		s.Put(h);
		
		b.FSetStart();
		HelpClass *hh = (HelpClass *)s.GetNObject();
		delete hh;
		
		int kk = 0;
	} catch (Exception *e) {
		delete e;
	}
	
	return 0;
}

