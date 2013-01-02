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
	StdOut::PrintLine(t.AddGMTOffset().ToText());
	StdOut::PrintLine(t.ToText());
	
	DateTime cmpl(1977, 03, 06);
	StdOut::PrintLine(cmpl.ToText("%d/%m/%Y %H:%M:%S"));
	if (cmpl.ToText("%d/%m/%Y %H:%M:%S") != "06/03/1977 00:00:00") {
		StdOut::PrintLine("DateTime instantiation error!");
		return -1;
	}
	if (cmpl.Year() != 1977 || cmpl.Month() != 03 || cmpl.Day() != 06) {
		StdOut::PrintLine("Cannot extract member variables");
		return -1;
	}
	
	DateTime cmpl2(1981, 12, 07, 00, 04, 05);
	StdOut::PrintLine(cmpl2.ToText("%d/%m/%Y %H:%M:%S"));
	if (cmpl2.ToText(L"%d/%m/%Y %H:%M:%S") != L"07/12/1981 00:04:05") {
		StdOut::PrintLine("DateTime instantiation error!");
		return -1;
	}
	if (cmpl2.Year() != 1981 || cmpl2.Month() != 12 || cmpl2.Day() != 07 || 
		cmpl2.Hour() != 00 || cmpl2.Minute() != 04 || cmpl2.Second() != 05) 
	{
		StdOut::PrintLine("Cannot extract member variables");
		return -1;
	}
	
	DateTime cpy = cmpl2.TotalDays();
	if (cpy != cmpl2) {
		StdOut::PrintLine("DateTime TotalDays composition doesn't work!");
		return -1;
	}
	if (cpy < cmpl2 || !(cpy <= cmpl2) || !(cpy == cmpl2) || cpy > cmpl2 || !(cpy >= cmpl2)) {
		StdOut::PrintLine("DateTime comparation error!");
		return -1;
	}
	if (cmpl > cmpl2 || cmpl >= cmpl2 || cmpl2 < cmpl || cmpl2 <= cmpl) {
		StdOut::PrintLine("DateTime comparation error!");
		return -1;
	}
	
	DateTime cpy2(cmpl2);
	if (cpy2 != cmpl2 || cpy2 != cpy) {
		StdOut::PrintLine("DateTime constructor composition doesn't work!");
		return -1;
	}
	
	DateTime datePartA = cmpl.DatePart();
	if (datePartA != cmpl) {
		StdOut::PrintLine("DateTime DatePart doesn't work!");
		return -1;
	}
	
	DateTime datePart = cmpl2.DatePart();
	StdOut::PrintLine(datePart.ToText("%d/%m/%Y %H:%M:%S"));
	if (datePart.ToText("%d/%m/%Y %H:%M:%S") != L"07/12/1981 00:00:00") {
		StdOut::PrintLine("DatePart doesn't work!");
		return -1;
	}
	
	DateTime timePart = cmpl2.TimePart();
	StdOut::PrintLine(timePart.ToText("%d/%m/%Y %H:%M:%S"));
	if (timePart.ToText("%d/%m/%Y %H:%M:%S") != "01/01/1970 00:04:05") {
		StdOut::PrintLine("TimePart doesn't work!");
		return -1;
	}
	
	DateTime temp = datePart + timePart;
	StdOut::PrintLine(temp.ToText("%d/%m/%Y %H:%M:%S"));
	
	if (cmpl2 != datePart + timePart) {
		StdOut::PrintLine("DateTime DatePart and TimePart don't work!");
		return -1;
	}
	
	DateTime substract = cmpl2 - timePart;
	StdOut::PrintLine(substract.ToText("%d/%m/%Y %H:%M:%S"));
	
	if (datePart != cmpl2 - timePart) {
		StdOut::PrintLine("Substraction doesn't work!");
		return -1;
	}
	
	if (!datePart.Equals(cmpl2 - timePart)) {
		StdOut::PrintLine("Equals doesn't work!");
		return -1;
	}
	
	printf("%d\r\n", datePart.Compare(cmpl2 - timePart));
	printf("%d\r\n", cmpl2.Compare(cmpl));
	printf("%d\r\n", cmpl.Compare(cmpl2));
	if (datePart.Compare(cmpl2 - timePart) != 0 || cmpl2.Compare(cmpl) >= 0 || cmpl.Compare(cmpl2) <= 0) {
		StdOut::PrintLine("Compare doesn't work!");
		return -1;
	}
	
	Text fparse = L"%d/%m/%Y %H:%M:%S";
	Text tparse = L"07/12/1981 00:04:05";
	StdOut::PrintLine(DateTime::Parse("%d/%m/%Y", "06/03/1977").ToText(L"%d/%m/%Y"));
	StdOut::PrintLine(DateTime::Parse(L"%d/%m/%Y %H:%M:%S", L"07/12/1981 00:04:05").ToText("%d/%m/%Y %H:%M:%S"));
	StdOut::PrintLine(DateTime::Parse(fparse, tparse).ToText(tparse));
	if (DateTime::Parse("%d/%m/%Y", "06/03/1977") != cmpl ||
		DateTime::Parse("%d/%m/%Y %H:%M:%S", "07/12/1981 00:04:05") != cmpl2 ||
		DateTime::Parse(fparse, tparse) != cmpl2) 
	{
		StdOut::PrintLine("Parse doesn't work!");
		return -1;
	}
	
	if (cmpl2.ToText(fparse) != tparse ||
		cmpl2.ToText(L"%d/%m/%Y %H:%M:%S") != L"07/12/1981 00:04:05" ||
		cmpl2.ToText("%d/%m/%Y %H:%M:%S") != "07/12/1981 00:04:05") 
	{
		StdOut::PrintLine("ToText doesn't work!");
		return -1; 
	}
	
	DateTime tudt = cmpl2.AddGMTOffset();
	StdOut::PrintLine(tudt.ToText("%d/%m/%Y %H:%M:%S"));
	if (tudt != DateTime::Parse("%d/%m/%Y %H:%M:%S", "06/12/1981 23:04:05")) {
		StdOut::PrintLine("ToUtcDateTime doesn't work!");
		return -1;
	}
	
	DateTime tlocal = tudt.RemoveGMTOffset();
	StdOut::PrintLine(tlocal.ToText("%d/%m/%Y %H:%M:%S"));
	if (tlocal != cmpl2) {
		StdOut::PrintLine("ToLocalDateTime doesn't work!");
		return -1;
	}

	return 0;
}

