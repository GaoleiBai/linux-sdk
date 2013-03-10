#include "testsqlite3.h"
#include "../LFC/LFC.h"

TestSQLite3::TestSQLite3()
{
}

TestSQLite3::~TestSQLite3()
{
}

int TestSQLite3::Perform()
{
	SQLite3Statement *s = NULL;
	
	try {
		SQLite3DB db("pruebas.db");
		db.SetTimeout(30000);
		db.Open();
		
		const char *queries[] = { 
			"CREATE TABLE IF NOT EXISTS customer (ID INT PRIMARY KEY ASC UNIQUE NOT NULL, NAME TEXT, AGE REAL)",
			"DELETE FROM customer",
			"INSERT INTO customer (ID, NAME, AGE) VALUES (1, 'Pepe', 12.5)", 
			"INSERT INTO customer (ID, NAME, AGE) VALUES (2, 'John', 11.5)", 
			"INSERT INTO customer (ID, NAME, AGE) VALUES (3, 'Roger', 15.5)", 
			"INSERT INTO customer (ID, NAME, AGE) VALUES (4, 'Albert', 16.5)", 
			"INSERT INTO customer (ID, NAME, AGE) VALUES (5, 'Terry', 14.5)", 
			"INSERT INTO customer (ID, NAME, AGE) VALUES (6, 'Noa', 19.5)", 
			NULL };
		
		for (int i=0; queries[i]; i++) {
			s = new SQLite3Statement(db, queries[i]);
			s->Exec();
			delete s;
		}
		
		SQLite3Statement s1(db, "SELECT ID, NAME, AGE FROM customer");
		SQLite3Recordset r1 = s1.ExecQuery();
		while (r1.Step())
			StdOut::PrintLine((Text)r1.GetInt(0) + "\t" + r1.GetText(1) + "\t" + r1.GetDouble(2));
	} catch (Exception *e) {
		delete e;
		if (s != NULL) delete s;
		return -1;
	}
	
	return 0;
}

