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
#ifndef TESTS_H
#define TESTS_H

#include "test_text.h"
#include "testdirectory.h"
#include "testdatetime.h"
#include "testadministration.h"
#include "testfile.h"
#include "testcollection.h"
#include "testdictionary.h"
#include "test_buffer.h"
#include "testserialization.h"
#include "testnumeric.h"
#include "testserialport.h"
#include "testthread.h"
#include "testdelegation.h"
#include "testnetwork.h"
#include "testsqlite3.h"
#include "testrandom.h"
#include "testwindow.h"

class Tests {
public:
	Tests();
	~Tests();
	static int Perform();
};

#endif