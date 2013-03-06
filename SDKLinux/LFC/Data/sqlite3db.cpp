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
   
#include "sqlite3db.h"
#include "dataexception.h"
#include "../Text/text.h"
#include <unistd.h>

SQLite3DB::SQLite3DB(const Text &connection_string)
{
	this->connection_string = new Text(connection_string);
	db_timeout = 60000;
	db = NULL;
}

SQLite3DB::~SQLite3DB()
{
	Close();
	delete connection_string;
}

Text SQLite3DB::ConnectionString()
{
	return *connection_string;
}

void SQLite3DB::SetTimeout(int milliseconds)
{
	db_timeout = milliseconds;
}

int SQLite3DB::GetTimeout()
{
	return db_timeout;
}

int SQLite3DB::busy_handler(void *params, int tryes)
{
	SQLite3DB *db = (SQLite3DB *)params;
	usleep(10000);
	return tryes * 10 < db->db_timeout ? 1 : 0;
}

bool SQLite3DB::IsOpen()
{
	return db != NULL;
}

void SQLite3DB::Open()
{
	char filename[10001];
	connection_string->GetAnsiString(filename, 10000);
	
	if (sqlite3_open(filename, &db) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);
	if (sqlite3_busy_timeout(db, db_timeout) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);
	if (sqlite3_busy_handler(db, SQLite3DB::busy_handler, this) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);
}

void SQLite3DB::Close()
{
	if (db == NULL) return;
	if (sqlite3_close(db) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);
	db = NULL;
}
