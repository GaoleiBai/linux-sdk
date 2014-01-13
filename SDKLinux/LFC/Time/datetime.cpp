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
#include <typeinfo>
#include "datetime.h"
#include "timeexception.h"
#include "../Text/text.h"
#include "../FileSystem/serializator.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void DateTime::init(int year, int month, int day, int hour, int minute, int second)
{
	if (year < 1970) throw new TimeException("Cannot build dates before 1970", __FILE__, __LINE__, __func__);
	if (month < 1 || month > 12) throw new TimeException("Months must be beetween 1 and 12", __FILE__, __LINE__, __func__);
	if (day < 1 || day > 31) throw new TimeException("Days must be between 1 and 31", __FILE__, __LINE__, __func__);
	
	struct tm tt;
	memset(&tt, 0, sizeof(tt));
	tt.tm_year = year - 1900;
	tt.tm_mon = month - 1;
	tt.tm_mday = day;
	tt.tm_hour = hour;
	tt.tm_min = minute;
	tt.tm_sec = second;
	time_t ttt = mktime(&tt);
	ttt += tt.tm_gmtoff;
	if (tt.tm_isdst == 1) ttt -= 3600;
	if (ttt < 0) throw new TimeException("Can't form DateTime with the current data.", __FILE__, __LINE__, __func__);
	currentTime.tv_sec = ttt;
	currentTime.tv_nsec = 0;
}

void DateTime::updatetmhelper()
{
	time_t secs = currentTime.tv_sec;
	struct tm *t = gmtime(&secs);
	tmhelper = *t;
}

/**
 * @brief Builds a DateTime object with the current DateTime
 */
DateTime::DateTime()
{
	clock_gettime(CLOCK_REALTIME, &currentTime);
	updatetmhelper();
}

/**
 * @brief Builds a copy of the DateTime &t object
 */
DateTime::DateTime(const DateTime &t)
{
	currentTime = t.currentTime;
	tmhelper = t.tmhelper;
}

DateTime::DateTime(const DateTime *t)
{
	currentTime = t->currentTime;
	tmhelper = t->tmhelper;
}

/**
 * @brief Builds a DateTime object with the number of days passed in the argument
 */
DateTime::DateTime(long double totalDays)
{
	long double secs = totalDays * 86400.0;
	currentTime.tv_sec = secs;
	currentTime.tv_nsec = (secs - currentTime.tv_sec) * 1000000000.0;
	updatetmhelper();
}

DateTime::DateTime(time_t t)
{
	currentTime.tv_sec = t;
	currentTime.tv_nsec = 0;
	updatetmhelper();
}

DateTime::DateTime(int year, int month, int day)
{
	init(year, month, day, 0, 0 , 0);
	updatetmhelper();
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
	init(year, month, day, hour, minute, second);
	updatetmhelper();
}

DateTime::~DateTime()
{
	
}

int DateTime::GMTOFF()
{
	struct tm *tt = localtime(&currentTime.tv_sec);
	return tt->tm_gmtoff;
}

DateTime DateTime::DatePart()
{
	return DateTime(Year(), Month(), Day());
}

int DateTime::Year()
{
	return tmhelper.tm_year + 1900;
}

int DateTime::Month()
{
	return tmhelper.tm_mon + 1;
}

int DateTime::Day()
{
	return tmhelper.tm_mday;
}

DateTime DateTime::TimePart()
{
	return DateTime(1970, 1, 1, Hour(), Minute(), Second());
}

int DateTime::Hour()
{
	return tmhelper.tm_hour;
}

int DateTime::Minute()
{
	return tmhelper.tm_min;
}

int DateTime::Second()
{
	return tmhelper.tm_sec;
}

unsigned long DateTime::NanoSeconds()
{
	return currentTime.tv_nsec;
}

int DateTime::WeekDay()
{
	return tmhelper.tm_wday;
}

int DateTime::YearDay()
{
	return tmhelper.tm_yday;
}

long double DateTime::TotalDays()
{
	long double d = currentTime.tv_sec;
	d += currentTime.tv_nsec / 1000000000.0;
	return d / 86400.0;
}

long double DateTime::TotalHours()
{
	return TotalDays() * 24;
}

long double DateTime::TotalSeconds()
{
	return TotalDays() * 86400;
}

DateTime & DateTime::operator =(const DateTime &d)
{
	currentTime = d.currentTime;
	tmhelper = d.tmhelper;
	return *this;
}

DateTime DateTime::operator +(const DateTime &d)
{
	return this->TotalDays() + ((DateTime *)&d)->TotalDays();
}

DateTime DateTime::operator -(const DateTime &d)
{
	return this->TotalDays() - ((DateTime *)&d)->TotalDays();
}

void DateTime::operator +=(const DateTime &t)
{
	*this = *this + ((DateTime *)&t)->TotalDays();
}

void DateTime::operator -=(const DateTime &t)
{
	*this = *this - ((DateTime *)&t)->TotalDays();
}

bool DateTime::operator ==(const DateTime &d)
{
	return currentTime.tv_sec == d.currentTime.tv_sec && currentTime.tv_nsec == d.currentTime.tv_nsec;
}

bool DateTime::operator !=(const DateTime &d)
{
	return currentTime.tv_sec != d.currentTime.tv_sec || currentTime.tv_nsec != d.currentTime.tv_nsec;
}

bool DateTime::operator >(const DateTime &d)
{
	if (this->currentTime.tv_sec > d.currentTime.tv_sec) return true;
	if (this->currentTime.tv_sec == d.currentTime.tv_sec && this->currentTime.tv_nsec > d.currentTime.tv_nsec) return true;
	return false;
}

bool DateTime::operator <(const DateTime &d)
{
	if (this->currentTime.tv_sec < d.currentTime.tv_sec) return true;
	if (this->currentTime.tv_sec == d.currentTime.tv_sec && this->currentTime.tv_nsec < d.currentTime.tv_nsec) return true;
	return false;
}

bool DateTime::operator >=(const DateTime &d)
{
	if (this->currentTime.tv_sec >= d.currentTime.tv_sec) return true;
	if (this->currentTime.tv_sec == d.currentTime.tv_sec && this->currentTime.tv_nsec >= d.currentTime.tv_nsec) return true;
	return false;
}

bool DateTime::operator <=(const DateTime &d)
{
	if (this->currentTime.tv_sec <= d.currentTime.tv_sec) return true;
	if (this->currentTime.tv_sec == d.currentTime.tv_sec && this->currentTime.tv_nsec <= d.currentTime.tv_nsec) return true;
	return false;
}

bool DateTime::Equals(const DateTime &d)
{
	return *this == d;
}

int DateTime::Compare(const NObject &o) 
{
	if (typeid(o) != typeid(DateTime)) 
		throw new TimeException(
			(Text)"Cannot compare a DateTime object with a object of type " + ((NObject *)&o)->ClassName(), 
			__FILE__, __LINE__, __func__);
	
	return Compare((DateTime &)o);
}

int DateTime::Compare(const DateTime &d)
{
	long int diff = this->currentTime.tv_sec - d.currentTime.tv_sec;
	if (diff) return -diff;
	diff = this->currentTime.tv_nsec - d.currentTime.tv_nsec;
	return -diff;
}

DateTime DateTime::Parse(const Text &format, const Text &strDate)
{
	return Parse(format.p, strDate.p);
}

DateTime DateTime::Parse(const char *format, const char *strDate)
{
	struct tm ttt;
	memset(&ttt, 0, sizeof(ttt));
	if (strptime(strDate, format, &ttt) == NULL) throw new TimeException("The format cannot allow to parse the date string", __FILE__, __LINE__, __func__);
	
	time_t tt = mktime(&ttt) + ttt.tm_gmtoff;
	long double dd = tt / 86400.0l;
	return DateTime(dd);
}

DateTime DateTime::Parse(const wchar_t *format, const wchar_t *strDate)
{
	char str1[1001];
	char str2[1001];
	wcstombs(str1, format, 1000);
	wcstombs(str2, strDate, 1000);
	return Parse(str1, str2);
}

NObject *DateTime::NewInstance()
{
	return new DateTime();
}

Text DateTime::ToText()
{
	char cadena[1001];
	strftime(cadena, 1000, "%m/%d/%Y %H:%M:%S", &tmhelper);
	return Text(cadena);
}

Text DateTime::ToText(const Text &format)
{
	return ToText(format.p);
}

Text DateTime::ToText(const char *format)
{
	char cadena[1001];
	strftime(cadena, 1000, format, &tmhelper);
	return Text(cadena);
}

Text DateTime::ToText(const wchar_t *format)
{
	char cadena[1001];
	wcstombs(cadena, format, 1000);
	return ToText(cadena);
}

DateTime DateTime::AddGMTOffset()
{
	double to_add = 1.0 * GMTOFF() / 86400.0;
	return DateTime(TotalDays() + to_add);
}

DateTime DateTime::RemoveGMTOffset()
{
	double to_add = 1.0 * GMTOFF() / 86400.0;
	return DateTime(TotalDays() - to_add);
}

void DateTime::SetUtcDateTime(const DateTime &t)
{
	clock_settime(CLOCK_REALTIME, &t.currentTime);
}

DateTime DateTime::LocalDateTime()
{
	return DateTime().AddGMTOffset();
}

int DateTime::COMPARER(const void *u, const void *v)
{
	DateTime **uu = (DateTime **)u;
	DateTime **vv = (DateTime **)v;
	return -((DateTime *)*uu)->Compare(**vv);
}

void DateTime::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put((char *)&currentTime, sizeof(currentTime));
}

void DateTime::Deserialize(const Serializator &s)
{
	((Serializator *)&s)->Get((char *)&currentTime, sizeof(currentTime));
	updatetmhelper();
}

unsigned long long DateTime::SystemTicks()
{
	struct timespec tini;
	clock_gettime(CLOCK_MONOTONIC, &tini);
	return (unsigned long long) tini.tv_sec * 1000000000 + tini.tv_nsec;
}
