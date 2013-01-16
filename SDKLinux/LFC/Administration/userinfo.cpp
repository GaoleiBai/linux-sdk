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
   
   
#include "userinfo.h"
#include "administrationexception.h"
#include "../Text/text.h"
#include "../Text/text_buffer.h"
#include <pwd.h>
#include <stdlib.h>

UserInfo::UserInfo(int userID)
{
	struct passwd *p = getpwuid(userID);
	if (p == NULL) throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	
	name = new Text(p->pw_name);
	userID = p->pw_uid;
	groupID = p->pw_gid;
	dir = new Text(p->pw_dir);
	shell = new Text(p->pw_shell);
}

UserInfo::UserInfo(const Text &name, int userID, int groupID, const Text &initialDirectory, const Text &defaultShell)
{
	this->name = new Text(name);
	this->userID = userID;
	this->groupID = groupID;
	this->dir = new Text(initialDirectory);
	this->shell = new Text(defaultShell);
}

UserInfo::UserInfo(const Text &username)
{
	char cadena[1001];
	((Text)username).GetAnsiString(cadena, 1000);
	struct passwd *p = getpwnam(cadena);
	if (p == NULL) throw new AdministrationException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	
	name = new Text(p->pw_name);
	userID = p->pw_uid;
	groupID = p->pw_gid;
	dir = new Text(p->pw_dir);
	shell = new Text(p->pw_shell);
}

UserInfo::~UserInfo()
{
	delete name;
	delete dir;
	delete shell;
}

Text UserInfo::Name()
{
	return *name;
}

int UserInfo::UserID()
{
	return userID;
}

int UserInfo::GroupID()
{
	return groupID;
}

Text UserInfo::InitialDirectory()
{
	return *dir;
}

Text UserInfo::DefaultShell()
{
	return *shell;
}

Text UserInfo::ToText()
{
	TextBuffer b;
	b.AppendLine((Text)name);
	b.AppendLine((Text)"User ID: " + userID);
	b.AppendLine((Text)"Group ID: " + groupID);
	b.AppendLine((Text)"Initial directory: " + dir);
	b.AppendLine((Text)"Default shell: " + shell);
	return b.ToText();
}

