#include "datetime.h"
#include "timeexception.h"
#include "../Text/text.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void DateTime::init(int year, int month, int day, int hour, int minute, int second)
{
	struct tm tt;
	memset(&tt, 0, sizeof(tt));
	tt.tm_year = year - 1900;
	tt.tm_mon = month - 1;
	tt.tm_mday = day;
	tt.tm_hour = hour;
	tt.tm_min = minute;
	tt.tm_sec = second;
	time_t ttt = mktime(&tt);
	if (ttt < 0) throw TimeException("Can't form DateTime with the current data.");
	currentTime.tv_sec = ttt;
	currentTime.tv_nsec = 0;
}

void DateTime::updatetmhelper()
{
	struct tm *t = localtime(&currentTime.tv_sec);
	tmhelper = *t;
}

DateTime::DateTime()
{
	clock_gettime(CLOCK_REALTIME, &currentTime);
	updatetmhelper();
}

DateTime::DateTime(const DateTime &t)
{
	currentTime = t.currentTime;
	updatetmhelper();
}

DateTime::DateTime(long double totalDays)
{
	long double secs = totalDays * 86400.0;
	currentTime.tv_sec = secs;
	currentTime.tv_nsec = (secs - currentTime.tv_sec) * 1000000000.0;
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
	return DateTime(0, 0, 0, Day(), Minute(), Second());
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

DateTime & DateTime::operator =(const long double days)
{
	double secs = (days * 86400);
	currentTime.tv_sec = secs;
	currentTime.tv_nsec = (secs - currentTime.tv_sec) * 1000000000;
	updatetmhelper();
}

DateTime & DateTime::operator =(const DateTime &d)
{
	currentTime = d.currentTime;
	tmhelper = d.tmhelper;
	return *this;
}

DateTime DateTime::operator +(const long double days)
{
	DateTime q = *this;
	
	double secs = (days * 86400);
	int secondsToAdd = secs;
	unsigned long nsecToAdd = (secs - secondsToAdd) * 1000000000;
	
	q.currentTime.tv_sec += secondsToAdd + (q.currentTime.tv_nsec + nsecToAdd) / 1000000000;
	q.currentTime.tv_nsec = (q.currentTime.tv_nsec + nsecToAdd) % 1000000000;
	q.updatetmhelper();
	
	return q;
}

DateTime DateTime::operator +(DateTime &d)
{
	return *this + d.TotalDays();
}

DateTime DateTime::operator -(const long double d)
{
	return *this + (-d);
}

DateTime DateTime::operator -(DateTime &d)
{
	return *this + (-d.TotalDays());
}

void DateTime::operator +=(const long double days)
{
	*this = *this + days;
}

void DateTime::operator +=(DateTime &t)
{
	*this = *this + t.TotalDays();
}

void DateTime::operator -=(const long double days)
{
	*this = *this - days;
}

void DateTime::operator -=(DateTime &t)
{
	*this = *this - t.TotalDays();
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

int DateTime::Compare(const DateTime &d)
{
	long int diff = this->currentTime.tv_sec - d.currentTime.tv_sec;
	if (diff) return diff;
	diff = this->currentTime.tv_nsec - d.currentTime.tv_nsec;
	return diff;
}

DateTime DateTime::Parse(const Text &format, const Text &strDate)
{
	return Parse(format.p, strDate.p);
}

DateTime DateTime::Parse(const char *format, const char *strDate)
{
	struct tm ttt;
	if (strptime(strDate, format, &ttt) == NULL) throw TimeException("The format cannot allow to parse the date string");
	
	return DateTime(1.0 * mktime(&ttt) / 1000.0);
}

DateTime DateTime::Parse(const wchar_t *format, const wchar_t *strDate)
{
	char str1[1001];
	char str2[1001];
	wcstombs(str1, format, 1000);
	wcstombs(str2, strDate, 1000);
	return Parse(str1, str2);
}

Text DateTime::ToText()
{
	return Text(asctime(&tmhelper));
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

DateTime DateTime::ToUtcDateTime()
{
	long double dd = TotalDays();
	dd += timezone / 86400.0;
	return DateTime(dd);
}

DateTime DateTime::FromUtcDateTime(DateTime &t)
{
	return DateTime(t.TotalDays() - timezone);
}

void DateTime::SetUtcDateTime(const DateTime &t)
{
	clock_settime(CLOCK_REALTIME, &t.currentTime);
}
