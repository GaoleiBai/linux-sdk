#include "testdelegation.h"
#include "../LFC/LFC.h"
#include "stdio.h"

TestDelegation::TestDelegation()
{
}

TestDelegation::~TestDelegation()
{
}

int TestDelegation::Perform()
{
	class A : public NObject
	{
	public:
		A() {};
		void *amethod(char *param) { 
			StdOut::PrintLine((Text)"Hello " + param + " world!!!");
			return (void *)"Wolomolo!!!"; 
		};
	};
	
	A aa;
	NDelegation d(&aa, (Delegate)&A::amethod);
	Text wolomolo = (char *)d.Execute((char *)"Aparam");
	StdOut::PrintLine(wolomolo);
	
	return 0;
}

