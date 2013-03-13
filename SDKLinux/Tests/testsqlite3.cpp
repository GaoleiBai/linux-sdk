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
			
		SQLite3Statement s2(db, "SELECT NAME, AGE FROM customer WHERE ID=?");
		s2.BindInteger(1, 3);
		SQLite3Recordset r2 = s2.ExecQuery();
		if (r2.Step())
			StdOut::PrintLine((Text)r2.GetText(0) + "\t" + r2.GetDouble(1));
			
		SQLite3Statement s3(db, "SELECT NAME, AGE FROM customer WHERE NAME=$name");
		s3.BindText("$name", "Roger");
		SQLite3Recordset r3 = s3.ExecQuery();
		if (r3.Step())
			StdOut::PrintLine((Text)r3.GetText(0) + "\t" + r3.GetDouble(1));
		
	} catch (Exception *e) {
		delete e;
		if (s != NULL) delete s;
		return -1;
	}
	
	return 0;
}

