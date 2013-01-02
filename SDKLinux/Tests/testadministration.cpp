#include "testadministration.h"
#include "../LFC/LFC.h"

TestAdministration::TestAdministration()
{
}

TestAdministration::~TestAdministration()
{
}

int TestAdministration::Perform()
{
	Collection<UserInfo *> users = Administration::Users();
	Collection<GroupInfo *> groups = Administration::Groups();
	
	for (int i=0; i<users.Count(); i++) 
		StdOut::PrintLine(users[i]->ToText());
	StdOut::PrintLine();
	
	for (int i=0; i<groups.Count(); i++)
		StdOut::PrintLine(groups[i]->ToText());
	StdOut::PrintLine();
	
	StdOut::PrintLine(Administration::GetRealUser().ToText());
	StdOut::PrintLine();
	StdOut::PrintLine(Administration::GetEffectiveUser().ToText());
	StdOut::PrintLine();
	StdOut::PrintLine(Administration::GetRealGroup().ToText());
	StdOut::PrintLine();
	StdOut::PrintLine(Administration::GetEffectiveGroup().ToText());
	StdOut::PrintLine();
	
	users.DeleteAndClear();
	groups.DeleteAndClear();
	
	try { Administration::Mount("/dev/sda3", "test", "fuseblk", 0, ""); } 
	catch (AdministrationException *e) { delete e; }
	try { Administration::Umount("test"); }
	catch (AdministrationException *e) { delete e; }
	
	Text hostname = Administration::GetHostName();
	try { Administration::SetHostName("pepito"); }
	catch (Exception *e) { delete e; }
	Text hostnamePepito = Administration::GetHostName();
	try { Administration::SetHostName(hostname); }
	catch (Exception *e) { delete e; }
	
	return 0;
}