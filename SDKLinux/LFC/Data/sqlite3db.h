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
#ifndef SQLITE3DB_H
#define SQLITE3DB_H

#include "../n_object.h"
#include <sqlite3.h>

class SQLite3DB : public NObject 
{
	friend class SQLite3Statement;
	
protected:
	int db_timeout;
	Text *connection_string;
	sqlite3 *db;
	
	static int busy_handler(void *params, int tryes);
	
public:
	SQLite3DB(const Text &connection_string);
	virtual ~SQLite3DB();

	Text ConnectionString();
	void SetTimeout(int milliseconds);
	int GetTimeout();
	bool IsOpen();
	void Open();
	void Close();
	

};

#endif // SQLITE3DB_H
