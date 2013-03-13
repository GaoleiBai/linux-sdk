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
#ifndef USERINFO_H
#define USERINFO_H

#include "../n_object.h"

class Text;

class UserInfo : public NObject {

public:
	UserInfo(int userID);
	UserInfo(const Text &name, int userID, int groupID, const Text &initialDirectory, const Text &defaultShell);
	UserInfo(const Text &userName);
	virtual ~UserInfo();
	
	Text Name();
	int UserID();
	int GroupID();
	Text InitialDirectory();
	Text DefaultShell();
	
	Text ToText();

private:
	Text *name;
	int userID;
	int groupID;
	Text *dir;
	Text *shell;
	
};

#endif // USERINFO_H
