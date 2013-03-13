/* 
* LFC Library - Linux toolkit
* 
* Copyright (C) 2012, 2013 Daniel Mosquera Villanueva 
* (milkatoffeecuco@gmail.com)
* This file is part of LFC Library.
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*
**/
#include "groupinfo.h"
#include "systemexception.h"
#include "../Text/text.h"
#include "../Text/text_buffer.h"
#include <grp.h>
#include <stdlib.h>

GroupInfo::GroupInfo(int groupID)
{
	struct group *g = getgrgid(groupID);
	if (g == NULL) throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	
	name = new Text(g->gr_name);
	groupID = g->gr_gid;
	users = new Collection<Text *>();
	for (int i=0; g->gr_mem[i]; i++) users->Add(new Text(g->gr_mem[i]));
}

GroupInfo::GroupInfo(const Text &name, int groupID, const Collection<Text *> &users)
{
	this->name = new Text(name);
	this->groupID = groupID;
	this->users = new Collection<Text *>(users);
}

GroupInfo::GroupInfo(const Text &groupName)
{
	char cadena[1001];
	((Text)groupName).GetAnsiString(cadena, 1000);
	struct group *g = getgrnam(cadena);
	if (g == NULL) throw new SystemException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	
	name = new Text(g->gr_name);
	groupID = g->gr_gid;
	users = new Collection<Text *>();
	for (int i=0; g->gr_mem[i]; i++) users->Add(new Text(g->gr_mem[i]));
}

GroupInfo::~GroupInfo()
{
	delete name;
	users->DeleteAndClear();
	delete users;
}

Text GroupInfo::Name()
{
	return *name;
}

int GroupInfo::GroupID()
{
	return groupID;
}

Collection<Text *> GroupInfo::Users()
{
	return *users;
}

Text GroupInfo::ToText()
{
	TextBuffer b;
	b.AppendLine((Text)name);
	b.AppendLine((Text)"Group ID: " + groupID);
	b.AppendLine((Text)"Users: " + Text::Join(*users, ", "));
	return b.ToText();
}
