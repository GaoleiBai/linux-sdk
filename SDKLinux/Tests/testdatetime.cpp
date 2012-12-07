#include "testdatetime.h"
#include "../LFC/LFC.h"
#include <stdio.h>

TestDateTime::TestDateTime()
{
}

TestDateTime::~TestDateTime()
{
}

int TestDateTime::Perform()
{
	DateTime t;
	t.ToText().PrintLine();
	
	t.ToUtcDateTime().ToText().PrintLine();
	
	DateTime cmpl(1977, 03, 06);
	if (cmpl.ToText("%d/%m/%Y %H:%M:%S") != "06/03/1977 00:00:00") {
		Text::PrintLine("DateTime instantiation error!");
		return -1;
	}
	if (cmpl.Year() != 1977 || cmpl.Month() != 03 || cmpl.Day() != 06) {
		Text::PrintLine("Cannot extract member variables");
		return -1;
	}
	
	DateTime cmpl2(1981, 12, 07, 03, 04, 05);
	if (cmpl2.ToText(L"%d/%m/%Y %H:%M:%S") != L"07/12/1981 03:04:05") {
		Text::PrintLine("DateTime instantiation error!");
		return -1;
	}
	if (cmpl2.Year() != 1981 || cmpl2.Month() != 12 || cmpl2.Day() != 07 || 
		cmpl2.Hour() != 03 || cmpl2.Minute() != 04 || cmpl2.Second() != 05) 
	{
		Text::PrintLine("Cannot extract member variables");
		return -1;
	}
	

	return 0;
}

