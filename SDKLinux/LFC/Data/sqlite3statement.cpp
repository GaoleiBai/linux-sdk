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
   
#include "sqlite3statement.h"
#include "sqlite3db.h"
#include "dataexception.h"
#include "../Text/text.h"

SQLite3Statement::SQLite3Statement(const SQLite3DB &database, const Text &query)
{
	this->query = new Text(query);
	db = database.db;
	
	int strquerylength = 2 * ((Text *)&query)->Length() + 1;
	char *strquery = new char[strquerylength];
	((Text *)&query)->GetAnsiString(strquery, strquerylength);
	int sqres = sqlite3_prepare(db, strquery, -1, &stmt, NULL);
	delete strquery;
	if (sqres != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);		
}

SQLite3Statement::~SQLite3Statement()
{
	if (sqlite3_finalize(stmt) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);		
	delete query;
	stmt = NULL;
	db = NULL;
}

