#include "text.h"
#include "text_exception.h"
#include <string.h>
#include <stdio.h>


Text &Text::aquireText(const char *s, int length, bool deletePrevious)
{
	if (deletePrevious) delete p;
	this->length = length;
	p = new char[length + 1];
	for (int i=0; i<length; i++) p[i] = s[i];
	p[length] = 0;
	return *this;
}

Text::Text()
{
	aquireText("", 0, false);
}

Text::Text(const char *t)
{
	aquireText(t, strlen(t), false);
}

Text::Text(const char *t, int length)
{
	aquireText(t, length, false);
}

Text::Text(const Text &t)
{
	aquireText(t.p, t.length, false);
}

Text::Text(bool b) 
{
	aquireText(b ? "true" : "false", b ? 4 : 5, true);
}

Text::Text(int i)
{
	char cadena[100];
	sprintf(cadena, "%i", i);
	aquireText(cadena, strlen(cadena), false);
}

Text::Text(float f) 
{
	char cadena[100];
	sprintf(cadena, "%f", f);
	aquireText(cadena, strlen(cadena), false);
}

Text::Text(double d)
{
	char cadena[100];
	sprintf(cadena, "%f", d);
	aquireText(cadena, strlen(cadena), false);
}

Text::~Text()
{
	delete p;
}

int Text::Length()
{
	return length;
}

char *Text::GetAnsiString()
{
	return p;
}

int Text::Compare(const char *t) 
{
	int tlength = strlen(t);
	int lenDiff = tlength - length;
	if (lenDiff) return lenDiff;
	
	for (int i=0; i<tlength && i<length; i++) {
		int dist = t[i] - p[i];
		if (dist) return dist;
	}
}

int Text::Compare(const Text &t)
{
	int lenDiff = t.length - length;
	if (lenDiff) return lenDiff;
	
	for (int i=0; i<t.length && i<length; i++) {
		int dist = t.p[i] - p[i];
		if (dist) return dist;
	}
}

Text Text::SubText(int ix)
{
	return SubText(ix, this->length - ix);
}

Text Text::SubText(int ix, int length)
{
	if (ix < 0) throw new TextException("Index out of bounds");
	if (ix + length > this->length) throw TextException("Text piece out of source Text");
	
	Text q;
	return q.aquireText(p + ix, length, true);
}

int Text::findIx(const char *c, int len)
{
	if (len == 0) return -1;
	
	int maxLen = len - 1;
	int maxLength = length - len + 1;
	for (int i = 0; i < maxLength; i++) {
		char *uu = p + i;
		char *vv = (char *)c;
		for (int j=0; j<len; j++) {
			if (*uu++ != *vv++) break;
			if (j == maxLen) return i;
		}
	}
	
	return -1;	
}

int Text::FindIx(const Text &t)
{
	return findIx(t.p, t.length);
}

int Text::FindIx(const char *t)
{
	int tlength = strlen(t);
	return findIx(t, tlength);
}

int Text::FindIx(Collection<char> &c)
{
	return FindIx(c, 0);
}

int Text::FindIx(const Text &t, int startIndex)
{
	if (startIndex < 0 || startIndex > t.length) throw new Exception("Index out of bounds");
	return findIx(t.p + startIndex, t.length - startIndex);
}

int Text::FindIx(const char *t, int startIndex)
{
	int tlength = strlen(t);
	if (startIndex < 0 || startIndex > tlength) throw new Exception("Index out of bounds");
	return findIx(t + startIndex, tlength - startIndex);
}

int Text::FindIx(Collection<char> &c, int startIndex) 
{
	for (int i=startIndex; i<length; i++) {
		if (c.Contains(p[i]))
			return i;
	}
	
	return -1;
}

Collection<int> &Text::ExtractIndexes(Collection<int> &destination, Text &textToFind)
{
	int ix = 0;
	
	while (ix < length) {
		ix = FindIx(textToFind, ix);
		if (ix == -1) break;
		destination.Add(ix);
		ix += textToFind.length;
	}
	
	return destination;
}

Collection<Text *> &Text::Split(Collection<Text *> &destination, Collection<char> &splitChars, bool removeEmptyEntries)
{
	int ix = 0, previx = 0;
	
	while (ix <= length) {
		ix = FindIx(splitChars, ix);
		if (ix == -1) ix = length;
		if (ix == previx) {
			if (!removeEmptyEntries) destination.Add(new Text());
		} else {
			destination.Add(new Text(p + previx, (int)(ix - previx)));
		}
		ix++;
		previx = ix;
	}
	
	return destination;
}

Collection<Text *> &Text::Split(Collection<Text *> &destination, Text &splitChars, bool removeEmptyEntries)
{
	Collection<char> cSplitChars;
	for (int i=0; i<splitChars.Length(); i++) cSplitChars.Add(splitChars[i]);
	return Split(destination, cSplitChars, removeEmptyEntries);
}

void Text::Print()
{
	printf("%s", p);
}

bool Text::Equals(const Text &t)
{
	return *this == t;
}

bool Text::Equals(const char *t)
{
	return *this == t;
}

bool Text::StartsWith(Text &t)
{
	return StartsWith(t.p, t.length);
}

bool Text::StartsWith(const char *t)
{
	return StartsWith(t, strlen(t));
}

bool Text::StartsWith(const char *t, int tlength)
{
	if (tlength > length) return false;
	int minLen = tlength < length ? tlength : length;
	for (int i = 0; i < minLen; i++)
		if (t[i] != p[i])
			return false;
	return true;	
}

bool Text::EndsWith(const Text &t)
{
	return EndsWith(t.p, t.length);
}

bool Text::EndsWith(const char *t)
{
	return EndsWith(t, strlen(t));
}

bool Text::EndsWith(const char *t, int len)
{
	if (length < len) return false;
	int deltat = length - len;
	for (int i = 0; i < len; i++)
		if (p[deltat + i] != t[i])
			return false;
	return true;
}

bool Text::Contains(const Text &t)
{
	return Contains(t.p, t.length);
}

bool Text::Contains(const char *t)
{
	return Contains(t, strlen(t));
}

bool Text::Contains(const char *t, int len)
{
	return findIx(t, len) != -1;
}

Text Text::operator +(const Text &t)
{
	Text q;
	delete q.p;
	q.length = length + t.length;
	q.p = new char[q.length + 1];
	strcpy(q.p, p);
	strcat(q.p + length, t.p);
	return q;
}

Text Text::operator +(const char *t)
{
	Text q;
	delete q.p;
	q.length = length + strlen(t);
	q.p = new char[q.length + 1];
	strcpy(q.p, p);
	strcat(q.p + length, t);
	return q;
}

Text Text::operator +(bool b)
{
	Text q = b;
	return *this + q;
}

Text Text::operator +(int i) 
{
	Text q = i;
	return *this + q;
}

Text Text::operator +(float f)
{
	Text q = f;
	return *this + q;
}

Text Text::operator +(double d)
{
	Text q = d;
	return *this + q;
}

Text &Text::operator +=(const Text &t)
{
	int qlength = length + t.length;
	char *q = new char[qlength + 1];
	strcpy(q, p);
	strcat(q + length, t.p);
	delete p;
	length = qlength;
	p = q;
	return *this;
}

Text &Text::operator +=(const char *t)
{
	int qlength = length + strlen(t);
	char *q = new char[qlength + 1];
	strcpy(q, p);
	strcat(q + length, t);
	delete p;
	length = qlength;
	p = q;
	return *this;
}

Text &Text::operator +=(bool b)
{
	return b ? *this += "true" : *this += "false";
}

Text &Text::operator +=(int i)
{
	char cadena[100];
	sprintf(cadena, "%d", i);
	return *this += cadena;
}

Text &Text::operator +=(float f)
{
	char cadena[100];
	sprintf(cadena, "%f", f);
	return *this += cadena;
}

Text &Text::operator +=(double d)
{
	char cadena[100];
	sprintf(cadena, "%f", d);
	return *this += cadena;
}

Text &Text::operator =(const Text &t)
{
	if (&t == this) return *this;
	aquireText(t.p, t.length, true);
	return *this;
}

Text &Text::operator =(const char *t)
{
	aquireText(t, strlen(t), true);
	return *this;
}

Text &Text::operator =(bool b)
{
	return aquireText(b ? "true" : "false", b ? 4 : 5, true);
}

Text &Text::operator =(int i)
{
	char cadena[100];
	sprintf(cadena, "%d", i);
	return aquireText(cadena, strlen(cadena), true);
}

Text &Text::operator =(float f)
{
	char cadena[100];
	sprintf(cadena, "%f", f);
	return aquireText(cadena, strlen(cadena), true);
}

Text &Text::operator =(double d)
{
	char cadena[100];
	sprintf(cadena, "%f", d);
	return aquireText(cadena, strlen(cadena), true);
}

bool Text::operator ==(const Text &t)
{
	if (&t == this) return true;
	if (length != t.length) return false;
	return Compare(t) == 0;
}

bool Text::operator ==(const char *t)
{
	int lt = strlen(t);
	if (lt != length) return false;
	return Compare(t) == 0;
}

bool Text::operator !=(const Text &t)
{
	return !(*this == t);
}

bool Text::operator !=(const char *t)
{
	return !(*this == t);
}

bool Text::operator <(const Text &t)
{
	return Compare(t) < 0;
}

bool Text::operator <(const char *t)
{
	return Compare(t) < 0;
}

bool Text::operator >(const Text &t)
{
	return Compare(t) > 0;
}

bool Text::operator >(const char *t)
{
	return Compare(t) > 0;
}

char &Text::operator [](const int ix)
{
	if (ix < 0 || ix >= length) throw TextException("Índice fuera de límites");
	return p[ix];
}
