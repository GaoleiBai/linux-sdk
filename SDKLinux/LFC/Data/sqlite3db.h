#ifndef SQLITE3DB_H
#define SQLITE3DB_H

#include "../n_object.h"
#include <sqlite3.h>

class SQLite3DB : public NObject 
{
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
	void Open();
	void Close();
	

};

#endif // SQLITE3DB_H
