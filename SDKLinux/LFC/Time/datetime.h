#ifndef DATETIME_H
#define DATETIME_H

#include "../n_object.h"
#include <time.h>

class Text;

class DateTime {

public:
	DateTime();
	DateTime(const DateTime &d);
	DateTime(long double totalDays);
	DateTime(int year, int month, int day);
	DateTime(int year, int month, int day, int hour, int minute, int second);
	virtual ~DateTime();
	
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
	
	DateTime &operator=(const long double days);
	DateTime &operator=(const DateTime &t);
	DateTime operator+(const long double days);
	DateTime operator+(DateTime &d);
	DateTime operator-(const long double days);
	DateTime operator-(DateTime &d);
	void operator+=(const long double days);
	void operator+=(DateTime &d);
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
	
	Text ToText();
	Text ToText(const char *format);
	Text ToText(const wchar_t *format);
	Text ToText(const Text &format);
	
	DateTime ToUtcDateTime();
	DateTime FromUtcDateTime(DateTime &d);
	static void SetUtcDateTime(const DateTime &d);

protected:

	void init(int year, int month, int day, int hour, int minute, int second);
	void updatetmhelper();

	bool isutc;
	struct timespec currentTime;
	struct tm tmhelper;

};

#endif // DATETIME_H
