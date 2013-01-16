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
   
   
#ifndef DATETIME_H
#define DATETIME_H

#include "../n_object.h"
#include <time.h>

class Text;

class DateTime : public NObject {

public:
	DateTime();
	DateTime(const DateTime &d);
	DateTime(const DateTime *d);
	DateTime(time_t t);
	DateTime(long double totalDays);
	DateTime(int year, int month, int day);
	DateTime(int year, int month, int day, int hour, int minute, int second);
	virtual ~DateTime();
	
	long double GMTOFF();
	
	DateTime DatePart();
	int Year();
	int Month();
	int Day();
	
	DateTime TimePart();
	int Hour();
	int Minute();
	int Second();
	unsigned long NanoSeconds();
	
	int WeekDay();
	int YearDay();
	
	long double TotalDays();
	
	DateTime &operator=(const time_t t);
	DateTime &operator=(const long double days);
	DateTime &operator=(const DateTime &t);
	DateTime operator+(const time_t t);
	DateTime operator+(const long double days);
	DateTime operator+(DateTime &d);
	DateTime operator-(const time_t t);
	DateTime operator-(const long double days);
	DateTime operator-(DateTime &d);
	void operator+=(const time_t t);
	void operator+=(const long double days);
	void operator+=(DateTime &d);
	void operator-=(const time_t t);
	void operator-=(const long double days);
	void operator-=(DateTime &d);
	bool operator==(const DateTime &d);
	bool operator!=(const DateTime &d);
	bool operator>(const DateTime &d);
	bool operator<(const DateTime &d);
	bool operator>=(const DateTime &d);
	bool operator<=(const DateTime &d);
	
	bool Equals(const DateTime &d);
	int Compare(const DateTime &d);
	
	static DateTime Parse(const Text &format, const Text &strDate);
	static DateTime Parse(const wchar_t *format, const wchar_t *strDate);
	static DateTime Parse(const char *format, const char *strDate);
	
	Text ToText(const char *format);
	Text ToText(const wchar_t *format);
	Text ToText(const Text &format);
	
	DateTime AddGMTOffset();
	DateTime RemoveGMTOffset();
	static void SetUtcDateTime(const DateTime &d);
	
	static int COMPARER(const void *u, const void *v);	

	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);

protected:

	void init(int year, int month, int day, int hour, int minute, int second);
	void updatetmhelper();
	void prepareGMTOFF();

	static long double gmtoff;
	struct timespec currentTime;
	struct tm tmhelper;

};

#endif // DATETIME_H
