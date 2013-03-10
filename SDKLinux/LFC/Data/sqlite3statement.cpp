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
#include "sqlite3recordset.h"
#include "../Text/text.h"
#include "../FileSystem/buffer.h"

SQLite3Statement::SQLite3Statement(const SQLite3DB &database, const Text &query)
{
	this->query = new Text(query);
	db = database.db;
	
	int strquerylength = 2 * ((Text *)&query)->Length() + 1;
	char *strquery = new char[strquerylength];
	((Text *)&query)->GetAnsiString(strquery, strquerylength);
	int sqres = sqlite3_prepare_v2(db, strquery, -1, &stmt, NULL);
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

void SQLite3Statement::Exec()
{
	if (sqlite3_step(stmt) != SQLITE_DONE)
		throw new DataException((Text)"Statement didn't run: " + sqlite3_errmsg(db), __FILE__, __LINE__, __func__);		
}

SQLite3Recordset SQLite3Statement::ExecQuery()
{
	return SQLite3Recordset(db, stmt);;
}

void SQLite3Statement::BindNull(int parameter)
{
	if (sqlite3_bind_null(stmt, parameter) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);		
}

void SQLite3Statement::BindInteger(int parameter, int value)
{
	if (sqlite3_bind_int(stmt, parameter, value) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);		
}

void SQLite3Statement::BindLong(int parameter, long value)
{
	if (sqlite3_bind_int64(stmt, parameter, value) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);			
}

void SQLite3Statement::BindDouble(int parameter, double value)
{
	if (sqlite3_bind_double(stmt, parameter, value) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);		
}

void deleteFunction(void *parameter) {
	delete (char *)parameter;
}

void SQLite3Statement::BindText(int parameter, const Text &t)
{
	int lenvalue = ((Text *)&t)->Length();
	char *value = new char[2 * lenvalue + 1];
	((Text *)&t)->GetAnsiString(value, 2 * lenvalue);
	
	if (sqlite3_bind_text(stmt, parameter, value, lenvalue, deleteFunction) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);			
}

void SQLite3Statement::BindBlob(int parameter, const Buffer &b)
{
	Buffer *bb = (Buffer *)&b;
	char *buffer = new char[bb->Length()];
	bb->FSetStart();
	bb->Read(buffer, bb->Length());

	if (sqlite3_bind_blob(stmt, parameter, buffer, bb->Length(), deleteFunction) != SQLITE_OK)
		throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);			
}

int SQLite3Statement::GetParameterIndex(const Text &parameter)
{
	int lname = ((Text *)&parameter)->Length();
	char *pname = new char[2 * lname + 1];
	((Text *)&parameter)->GetAnsiString(pname, 2 * lname);
	
	int ix = sqlite3_bind_parameter_index(stmt, pname);
	delete pname;
	if (ix == 0) 
		throw new DataException((Text)"Parameter " + parameter + " not found", __FILE__, __LINE__, __func__);
}

void SQLite3Statement::BindNull(const Text &parameter)
{
	BindNull(GetParameterIndex(parameter));
}

void SQLite3Statement::BindInteger(const Text &parameter, int value)
{
	BindInteger(GetParameterIndex(parameter), value);
}

void SQLite3Statement::BindLong(const Text &parameter, long value)
{
	BindLong(GetParameterIndex(parameter), value);
}

void SQLite3Statement::BindDouble(const Text &parameter, double value)
{
	BindDouble(GetParameterIndex(parameter), value);
}

void SQLite3Statement::BindText(const Text &parameter, const Text &value)
{
	BindText(GetParameterIndex(parameter), value);
}

void SQLite3Statement::BindBlob(const Text &parameter, const Buffer &value)
{
	BindBlob(GetParameterIndex(parameter), value);
}