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
#ifndef GROUPINFO_H
#define GROUPINFO_H

#include "../Collections/collection.h"

class Text;

class GroupInfo : public NObject {

public:
	GroupInfo(int groupID);
	GroupInfo(const Text &name, int groupID, const Collection<Text *> &users);
	GroupInfo(const Text &groupName);
	virtual ~GroupInfo();
	
	Text Name();
	int GroupID();
	Collection<Text *> Users();
	
	virtual Text ToText();

private:
	Text *name;
	int groupID;
	Collection<Text *> *users;

};

#endif // GROUPINFO_H
