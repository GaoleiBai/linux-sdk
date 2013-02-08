/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva (daniel.m.v@terra.es)
   This file is part of LFC Library.

   LFC Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   LFC Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with LFC Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA. or see http://www.gnu.org/licenses/. */
   
   
#include "system.h"
#include "systemexception.h"
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
#include <time.h>

System::System()
{
}

System::~System()
{
}

Collection<GroupInfo *> System::Groups()
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
	
	if (errno != 0) throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__); 
	return cgi;
}

Collection<UserInfo *> System::Users()
{
	Collection<UserInfo *> cui;
	struct passwd *u;
	
	errno = 0;
	setpwent();
	while ((u = getpwent()) != NULL && errno == 0) {
		cui.Add(new UserInfo((Text)u->pw_name, u->pw_uid, u->pw_gid, (Text)u->pw_dir, (Text)u->pw_shell));
	}
	endpwent();
	
	if (errno != 0) 
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return cui;
}

uid_t System::GetRealUserID()
{
	return getuid();
}

uid_t System::GetEffectiveUserID()
{
	return geteuid();
}

gid_t System::GetRealGroupID()
{
	return getgid();
}

gid_t System::GetEffectiveGroupID()
{
	return getegid();
}

UserInfo System::GetRealUser()
{
	return (UserInfo)GetRealUserID();
}

UserInfo System::GetEffectiveUser()
{
	return (UserInfo)GetEffectiveUserID();
}

GroupInfo System::GetRealGroup()
{
	return (GroupInfo)GetRealGroupID();
}

GroupInfo System::GetEffectiveGroup()
{
	return (GroupInfo)GetEffectiveGroupID();
}

void System::SetRealUserID(uid_t userID)
{
	if (setuid(userID))
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void System::SetEffectiveUserID(uid_t userID)
{
	if (seteuid(userID))
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);	
}

void System::SetRealGroupID(gid_t groupID)
{
	if (setgid(groupID))
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void System::SetEffectiveGroupID(gid_t groupID)
{
	if (setegid(groupID))
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void System::SetHostName(const Text &hostname)
{
	char cadena[1001];
	((Text *) &hostname)->GetAnsiString(cadena, 1000);
	if (sethostname(cadena, strlen(cadena)))
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

Text System::GetHostName()
{
	char cadena[1001];	
	gethostname(cadena, 1000);
	return (Text)cadena;
}

void System::Mount(
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
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void System::Umount(const Text &path)
{
	char cadena[1001];
	((Text *) &path)->GetAnsiString(cadena, 1000);
	
	if (umount(cadena))
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);		
}

void System::Umount(const Text &path, int UMF_UMountFlags)
{
	char cadena[1001];
	((Text *) &path)->GetAnsiString(cadena, 1000);
	
	if (umount2(cadena, UMF_UMountFlags))
		throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);		
}

unsigned long System::GetNanoTicks()
{
	struct timespec ticks;
	clock_gettime(CLOCK_MONOTONIC, &ticks);
	return (unsigned long)ticks.tv_sec * 1000000000 + ticks.tv_nsec;
}