#include "administration.h"
#include "administrationexception.h"
#include "groupinfo.h"
#include "userinfo.h"
#include "../Text/text.h"
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/mount.h>

Administration::Administration()
{
}

Administration::~Administration()
{
}

Collection<GroupInfo *> Administration::Groups()
{
	Collection<GroupInfo *> cgi;
	struct group *g;
	Collection<Text *> users;
	
	setgrent();
	while ((g = getgrent()) != NULL) {
		users.Clear();
		for (int i=0; g->gr_mem[i] != NULL; i++) {
			users.Add(new Text(g->gr_mem[i]));			
		}
		cgi.Add(new GroupInfo((Text)g->gr_name, g->gr_gid, users));
	}
	endgrent();
	
	if (errno != 0) throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__); 
	return cgi;
}

Collection<UserInfo *> Administration::Users()
{
	Collection<UserInfo *> cui;
	struct passwd *u;
	
	setpwent();
	while ((u = getpwent()) != NULL) {
		cui.Add(new UserInfo((Text)u->pw_name, u->pw_uid, u->pw_gid, (Text)u->pw_dir, (Text)u->pw_shell));
	}
	endpwent();
	
	if (errno != 0) throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return cui;
}

uid_t Administration::GetRealUserID()
{
	return getuid();
}

uid_t Administration::GetEffectiveUserID()
{
	return geteuid();
}

gid_t Administration::GetRealGroupID()
{
	return getgid();
}

gid_t Administration::GetEffectiveGroupID()
{
	return getegid();
}

UserInfo Administration::GetRealUser()
{
	return (UserInfo)GetRealUserID();
}

UserInfo Administration::GetEffectiveUser()
{
	return (UserInfo)GetEffectiveUserID();
}

GroupInfo Administration::GetRealGroup()
{
	return (GroupInfo)GetRealGroupID();
}

GroupInfo Administration::GetEffectiveGroup()
{
	return (GroupInfo)GetEffectiveGroupID();
}

void Administration::SetRealUserID(uid_t userID)
{
	if (setuid(userID))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void Administration::SetEffectiveUserID(uid_t userID)
{
	if (seteuid(userID))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);	
}

void Administration::SetRealGroupID(gid_t groupID)
{
	if (setgid(groupID))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void Administration::SetEffectiveGroupID(gid_t groupID)
{
	if (setegid(groupID))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void Administration::SetHostName(const Text &hostname)
{
	char cadena[1001];
	((Text *) &hostname)->GetAnsiString(cadena, 1000);
	if (sethostname(cadena, strlen(cadena)))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

Text Administration::GetHostName()
{
	char cadena[1001];	
	gethostname(cadena, 1000);
	return (Text)cadena;
}

void Administration::Mount(
	const Text &deviceName, const Text &targetDirectory, 
	const Text &fileSystemName, unsigned long MF_MountFlags, 
	const Text &data)
{
	char dn[1001];
	char td[1001];
	char fsn[1001];
	char d[1001];
	
	((Text *) &deviceName)->GetAnsiString(dn, 1000);
	((Text *) &targetDirectory)->GetAnsiString(td, 1000);
	((Text *) &fileSystemName)->GetAnsiString(fsn, 1000);
	((Text *) &data)->GetAnsiString(d, 1000);
		
	if (mount(dn, td, fsn, MF_MountFlags, d))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void Administration::Umount(const Text &path)
{
	char cadena[1001];
	((Text *) &path)->GetAnsiString(cadena, 1000);
	
	if (umount(cadena))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);		
}

void Administration::Umount(const Text &path, int UMF_UMountFlags)
{
	char cadena[1001];
	((Text *) &path)->GetAnsiString(cadena, 1000);
	
	if (umount2(cadena, UMF_UMountFlags))
		throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);		
}