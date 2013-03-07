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
   
#ifndef SQLITE3RECORDSET_H
#define SQLITE3RECORDSET_H

#include "../n_object.h"
#include <sqlite3.h>

class Buffer;

class SQLite3Recordset : public NObject {
	friend class SQLite3Statement;
	
	sqlite3 *db;
	sqlite3_stmt *stmt;
	SQLite3Recordset(sqlite3 *db, sqlite3_stmt *stmt);
	void CheckColumnIndex(int column);
public:
	SQLite3Recordset(const SQLite3Recordset &r);
	virtual ~SQLite3Recordset();

	int Columns();
	bool ExistsColumn(int column);
	bool Step();
	bool IsNull(int column);
	int GetInt(int column);
	long GetLong(int column);
	double GetDouble(int column);
	Text GetText(int column);
	Buffer GetBlob(int column);
	
};

#endif // SQLITE3RECORDSET_H
