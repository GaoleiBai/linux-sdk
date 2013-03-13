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
#include "sqlite3recordset.h"
#include "dataexception.h"
#include "../Text/text.h"
#include "../FileSystem/buffer.h"

SQLite3Recordset::SQLite3Recordset(sqlite3 *db, sqlite3_stmt *stmt)
{
	this->db = db;
	this->stmt = stmt;
}

SQLite3Recordset::SQLite3Recordset(const SQLite3Recordset &r)
{
	db = r.db;
	stmt = r.stmt;
}

SQLite3Recordset::~SQLite3Recordset()
{
}

bool SQLite3Recordset::Step()
{
	int res = sqlite3_step(stmt);
	if (res == SQLITE_ROW) return true;
	else if (res == SQLITE_DONE) return false;
	else throw new DataException(sqlite3_errmsg(db), __FILE__, __LINE__, __func__);		
}

int SQLite3Recordset::Columns()
{
	return sqlite3_column_count(stmt);
}

bool SQLite3Recordset::ExistsColumn(int column)
{
	if (column < 0) return false;
	if (column >= Columns()) return false;
	return true;
}

void SQLite3Recordset::CheckColumnIndex(int column)
{
	if (column < 0) 
		throw new DataException((Text)"Incorrect column " + column, __FILE__, __LINE__, __func__);
	if (column >= Columns())
		throw new DataException((Text)"Column index does not exist " + column + ": " + column + " columns", __FILE__, __LINE__, __func__);
}

bool SQLite3Recordset::IsNull(int column)
{
	CheckColumnIndex(column);
	return sqlite3_column_type(stmt, column) == SQLITE_NULL;
}

bool SQLite3Recordset::IsInteger(int column)
{
	CheckColumnIndex(column);
	return sqlite3_column_type(stmt, column) == SQLITE_INTEGER;
}

bool SQLite3Recordset::IsLong(int column)
{
	CheckColumnIndex(column);
	return sqlite3_column_type(stmt, column) == SQLITE_INTEGER;	
}

bool SQLite3Recordset::IsDouble(int column)
{
	CheckColumnIndex(column);
	return sqlite3_column_type(stmt, column) == SQLITE_FLOAT;
}

bool SQLite3Recordset::IsText(int column)
{
	CheckColumnIndex(column);
	return sqlite3_column_type(stmt, column) == SQLITE3_TEXT;	
}

bool SQLite3Recordset::IsBlob(int column)
{
	CheckColumnIndex(column);
	return sqlite3_column_type(stmt, column) == SQLITE_BLOB;	
}

int SQLite3Recordset::GetInt(int column)
{
	CheckColumnIndex(column);
	if (!IsInteger(column))
		throw new DataException((Text)"Unspected type in column " + column, __FILE__, __LINE__, __func__);
	return sqlite3_column_int(stmt, column);
}

long SQLite3Recordset::GetLong(int column)
{
	CheckColumnIndex(column);
	if (!IsInteger(column))
		throw new DataException((Text)"Unspected type in column " + column, __FILE__, __LINE__, __func__);
	return sqlite3_column_int64(stmt, column);
}

double SQLite3Recordset::GetDouble(int column)
{
	CheckColumnIndex(column);
	if (!IsDouble(column))
		throw new DataException((Text)"Unspected type in column " + column, __FILE__, __LINE__, __func__);
	return sqlite3_column_double(stmt, column);
}

Text SQLite3Recordset::GetText(int column)
{
	CheckColumnIndex(column);
	if (!IsText(column))
		throw new DataException((Text)"Unspected type in column " + column, __FILE__, __LINE__, __func__);
	return Text((char *)sqlite3_column_text(stmt, column), sqlite3_column_bytes(stmt, column));
}

Buffer SQLite3Recordset::GetBlob(int column)
{
	CheckColumnIndex(column);
	if (!IsBlob(column))
		throw new DataException((Text)"Unspected type in column " + column, __FILE__, __LINE__, __func__);
	return Buffer((char *)sqlite3_column_blob(stmt, column), sqlite3_column_bytes(stmt, column));
}
