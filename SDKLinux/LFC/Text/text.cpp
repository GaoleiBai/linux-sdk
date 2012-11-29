#include "text.h"
#include "text_exception.h"
#include <string.h>
#include <stdio.h>
#include <wchar.h>

Text &Text::aquireText(const char *s, int len, bool deletePrevious)
{
	if (deletePrevious) delete p;
	length = len;
	p = new wchar_t[len + 1];
	for (int i=0; i<len; i++) p[i] = s[i];
	p[len] = 0;
	return *this;
}

Text &Text::aquireText(const wchar_t *s, int len, bool deletePrevious)
{
	if (deletePrevious) delete p;
	length = len;
	p = new wchar_t[len + 1];
	for (int i=0; i<len; i++) p[i] = s[i];
	p[len] = 0;
	return *this;
}

Text &Text::appendText(const wchar_t *t, int len)
{
	int qlength = length + len;
	wchar_t *q = new wchar_t[qlength + 1];
	wchar_t *qq = q;
	wchar_t *pp = p;
	wchar_t *tt = (wchar_t *)t;
	while (*pp) *qq++ = *pp++;
	while (*tt) *qq++ = *tt++;
	*qq = 0;
	delete p;
	length = qlength;
	p = q;
	return *this;
}

Text &Text::appendText(const char *t, int len)
{
	int qlength = length + len;
	wchar_t *q = new wchar_t[qlength + 1];
	wchar_t *qq = q;
	wchar_t *pp = p;
	char *tt = (char *)t;
	while (*pp) *qq++ = *pp++;
	while (*tt) *qq++ = *tt++;
	*qq = 0;
	delete p;
	length = qlength;
	p = q;
	return *this;
}

Text &Text::joinText(const wchar_t *t, int tlen, const char *u, int ulen, bool deletePrevious)
{
	int qlength = tlen + ulen;
	wchar_t *q = new wchar_t[qlength + 1];
	wchar_t *qq = q;
	wchar_t *tt = (wchar_t *)t;
	char *uu = (char *)u;
	while (*tt) *qq++ = *tt++;
	while (*uu) *qq++ = *uu++;
	*qq = 0;
	if (deletePrevious) delete p;
	length = qlength;
	p = q;
	return *this;
}

Text &Text::joinText(const wchar_t *t, int tlen, const wchar_t *u, int ulen, bool deletePrevious)
{
	int qlength = tlen + ulen;
	wchar_t *q = new wchar_t[qlength + 1];
	wchar_t *qq = q;
	wchar_t *tt = (wchar_t *)t;
	wchar_t *uu = (wchar_t *)u;
	while (*tt) *qq++ = *tt++;
	while (*uu) *qq++ = *uu++;
	*qq = 0;
	if (deletePrevious) delete p;
	length = qlength;
	p = q;
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

Text::Text(const char *t, int len)
{
	aquireText(t, len, false);
}

Text::Text(const wchar_t *t)
{
	aquireText(t, wcslen(t), false);
}

Text::Text(const wchar_t *t, int len)
{
	aquireText(t, len, false);
}

Text::Text(const wchar_t *t, int tlen, const wchar_t *u, int ulen)
{
	joinText(t, tlen, u, ulen, false);
}

Text::Text(const Text &t)
{
	aquireText(t.p, t.length, false);
}

Text::Text(const Text &t, const Text &u)
{
	joinText(t.p, t.length, u.p, u.length, false);
}

Text::Text(bool b) 
{
	aquireText(b ? "true" : "false", b ? 4 : 5, false);
}

Text::Text(char c)
{
	aquireText(&c, 1, false);
}

Text::Text(wchar_t c)
{
	aquireText(&c, 1, false);
}

Text::Text(short int i)
{
	char cadena[100];
	sprintf(cadena, "%hi", i);
	aquireText(cadena, strlen(cadena), false);	
}

Text::Text(int i)
{
	char cadena[100];
	sprintf(cadena, "%i", i);
	aquireText(cadena, strlen(cadena), false);
}

Text::Text(long int i)
{
	char cadena[100];
	sprintf(cadena, "%li", i);
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

void Text::GetAnsiString(char *buffer, int &len)
{
	int i = 0;
	wchar_t *q = p;
	char *r = buffer;
	while (i < len && *q) *r++ = *q++;
	len = i;
}

void Text::GetWideString(wchar_t *buffer, int &len)
{
	int i = 0;
	wchar_t *q = p;
	wchar_t *r = buffer;
	while (i < len && *q) *r++ = *q++;
	len = i;	
}

int Text::Compare(const char *t)
{
	return Compare(t, strlen(t));
}

int Text::Compare(const char *t, int len) 
{
	int minLen = len < length ? len : length;
	wchar_t *pp = p;
	char *tt = (char *)t;
	for (int i=0; i<minLen; i++) {
		int dist = *pp++ - *tt++;
		if (dist) return dist;
	}
	
	int lenDiff = len - length;
	if (lenDiff) return lenDiff;
}

int Text::Compare(const wchar_t *t)
{
	return Compare(t, wcslen(t));
}

int Text::Compare(const wchar_t *t, int len)
{
	int minLen = len < length ? len : length;
	wchar_t *pp = p;
	wchar_t *tt = (wchar_t *)t;
	for (int i=0; i<minLen; i++) {
		int dist = *pp++ - *tt++;
		if (dist) return dist;
	}
	
	int lenDiff = len - length;
	if (lenDiff) return lenDiff;
}

int Text::Compare(const Text &t)
{
	return Compare(t.p, t.length);
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
		wchar_t *uu = p + i;
		char *vv = (char *)c;
		for (int j=0; j<len; j++) {
			if (*uu++ != *vv++) break;
			if (j == maxLen) return i;
		}
	}
	
	return -1;	
}

int Text::findIx(const wchar_t *c, int len)
{
	if (len == 0) return -1;
	
	int maxLen = len - 1;
	int maxLength = length - len + 1;
	for (int i = 0; i < maxLength; i++) {
		wchar_t *uu = p + i;
		wchar_t *vv = (wchar_t *)c;
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
	printf("%S", p);
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

bool Text::StartsWith(const char *t, int len)
{
	if (len > length) return false;
	int minLen = len < length ? len : length;
	for (int i = 0; i < minLen; i++)
		if (t[i] != p[i])
			return false;
	return true;	
}

bool Text::StartsWith(const wchar_t *t)
{
	return StartsWith(t, wcslen(t));
}

bool Text::StartsWith(const wchar_t *t, int len)
{
	if (len > length) return false;
	int minLen = len < length ? len : length;
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
	wchar_t *pp = p + deltat;
	char *tt = (char *)t;
	for (int i = 0; i < len; i++)
		if (*pp++ != *tt++)
			return false;
	return true;
}

bool Text::EndsWith(const wchar_t *t)
{
	return EndsWith(t, wcslen(t));
}

bool Text::EndsWith(const wchar_t *t, int len)
{
	if (length < len) return false;
	int deltat = length - len;
	wchar_t *pp = p + deltat;
	wchar_t *tt = (wchar_t *)t;
	for (int i = 0; i < len; i++)
		if (*pp++ != *tt++)
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

bool Text::Contains(const wchar_t *t)
{
	return Contains(t, wcslen(t));
}

bool Text::Contains(const wchar_t *t, int len)
{
	return findIx(t, len) != -1;
}

Text Text::operator +(const Text &t)
{
	Text q;
	return q.joinText(p, length, t.p, t.length, true);
}

Text Text::operator +(const char *t)
{
	Text q;
	return q.joinText(p, length, t, strlen(t), true);
}

Text Text::operator +(const wchar_t *t)
{
	Text q;
	return q.joinText(p, length, t, wcslen(t), true);
}

Text Text::operator +(bool b)
{
	Text q = b;
	return *this + q;
}

Text Text::operator +(char c)
{
	Text q = c;
	return *this + c;
}

Text Text::operator +(wchar_t c)
{
	Text q = c;
	return *this + c;
}

Text Text::operator +(short int i)
{
	Text q = i;
	return *this + q;
}

Text Text::operator +(int i) 
{
	Text q = i;
	return *this + q;
}

Text Text::operator +(long int i)
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
	return appendText(t.p, t.length);
}

Text &Text::operator +=(const char *t)
{
	return appendText(t, strlen(t));
}

Text &Text::operator +=(const wchar_t *t)
{
	return appendText(t, wcslen(t));
}

Text &Text::operator +=(bool b)
{
	return appendText(b ? "true" : "false", b ? 4 : 5);
}

Text &Text::operator +=(char c)
{
	return appendText(&c, 1);
}

Text &Text::operator +=(wchar_t c)
{
	return appendText(&c, 1);
}

Text &Text::operator +=(short int i)
{
	char cadena[100];
	sprintf(cadena, "%hi", i);
	return *this += cadena;	
}

Text &Text::operator +=(int i)
{
	char cadena[100];
	sprintf(cadena, "%i", i);
	return *this += cadena;
}

Text &Text::operator +=(long int i)
{
	char cadena[100];
	sprintf(cadena, "%li", i);
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
	return aquireText(t.p, t.length, true);
}

Text &Text::operator =(const char *t)
{
	return aquireText(t, strlen(t), true);
}

Text &Text::operator =(const wchar_t *t)
{
	return aquireText(t, wcslen(t), true);
}

Text &Text::operator =(bool b)
{
	return aquireText(b ? "true" : "false", b ? 4 : 5, true);
}

Text &Text::operator =(char c)
{
	return aquireText(&c, 1, true);
}

Text &Text::operator =(wchar_t c)
{
	return aquireText(&c, 1, true);
}

Text &Text::operator =(short int i)
{
	char cadena[100];
	sprintf(cadena, "%hi", i);
	return aquireText(cadena, strlen(cadena), true);
}

Text &Text::operator =(int i)
{
	char cadena[100];
	sprintf(cadena, "%i", i);
	return aquireText(cadena, strlen(cadena), true);
}

Text &Text::operator =(long int i)
{
	char cadena[100];
	sprintf(cadena, "%li", i);
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
	return Compare(t, lt) == 0;
}

bool Text::operator ==(const wchar_t *t)
{
	int lt = wcslen(t);
	if (lt != length) return false;
	return Compare(t, lt) == 0;
}

bool Text::operator !=(const Text &t)
{
	return !(*this == t);
}

bool Text::operator !=(const char *t)
{
	return !(*this == t);
}

bool Text::operator !=(const wchar_t *t)
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

bool Text::operator <(const wchar_t *t)
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

bool Text::operator >(const wchar_t *t)
{
	return Compare(t) > 0;
}

bool Text::operator <=(const Text &t)
{
	return Compare(t) <= 0;
}

bool Text::operator <=(const char *t)
{
	return Compare(t) <= 0;
}

bool Text::operator <=(const wchar_t *t)
{
	return Compare(t) <= 0;
}

bool Text::operator >=(const Text &t)
{
	return Compare(t) >= 0;
}

bool Text::operator >=(const char *t)
{
	return Compare(t) >= 0;
}

bool Text::operator >=(const wchar_t *t)
{
	return Compare(t) >= 0;
}

wchar_t &Text::operator [](const int ix)
{
	if (ix < 0 || ix >= length) throw TextException("Índice fuera de límites");
	return p[ix];
}
