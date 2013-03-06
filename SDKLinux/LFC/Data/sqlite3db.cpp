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
