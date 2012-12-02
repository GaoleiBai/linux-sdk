#include "text.h"
#include "text_buffer.h"
#include "text_exception.h"
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

char *Text::write(int posdest, char *dest, int ldest, int possrc, const char *src, int lsrc)
{
	int lldest = ldest;
	if (lsrc < ldest - posdest) lldest = posdest + lsrc;
	char *dd = dest + posdest;
	char *ss = (char *)src;
	for (int i=posdest; i<lldest; i++) *dd++ = *ss++;
	*dd = 0;
	return dest;
}

wchar_t *Text::write(int posdest, wchar_t *dest, int ldest, int possrc, const char *src, int lsrc)
{
	int lldest = ldest;
	if (lsrc < ldest - posdest) lldest = posdest + lsrc;
	wchar_t *dd = dest + posdest;
	char *ss = (char *)src;
	for (int i=posdest; i<lldest; i++) *dd++ = *ss++;
	*dd = 0;
	return dest;
}

wchar_t *Text::write(int posdest, wchar_t *dest, int ldest, int possrc, const wchar_t *src, int lsrc)
{
	int lldest = ldest;
	if (lsrc < ldest - posdest) lldest = posdest + lsrc;
	wchar_t *dd = dest + posdest;
	wchar_t *ss = (wchar_t *)src;
	for (int i=posdest; i<lldest; i++) *dd++ = *ss++;
	*dd = 0;
	return dest;
}

int Text::findIx(int strpos, const wchar_t *str, int strlen, int findpos, const char *find, int findlen)
{
	if (findlen > strlen) return -1;
	int maxFindLen = findlen - 1;
	int maxlen = strlen - findlen;
	for (int i=strpos; i<strlen; i++) {
		wchar_t *ss = (wchar_t *)(str + i);
		char *ff = (char *)find;
		for (int j = findpos; j<findlen; j++) {
			if (*ss++ != *ff++) break;
			if (j == maxFindLen) return i;
		}
	}
	
	return -1;
}

int Text::findIx(int strpos, const wchar_t *str, int strlen, int findpos, const wchar_t *find, int findlen)
{
	if (findlen > strlen) return - 1;
	int maxFindLen = findlen - 1;
	int maxlen = strlen - findlen;
	for (int i=strpos; i<strlen; i++) {
		wchar_t *ss = (wchar_t *)(str + i);
		wchar_t *ff = (wchar_t *)find;
		for (int j = findpos; j<findlen; j++) {
			if (*ss++ != *ff++) break;
			if (j == maxFindLen) return i;
		}
	}
	
	return -1;
}

Text &Text::aquireText(const char *s, int len, bool deletePrevious)
{
	if (deletePrevious) delete p;
	length = len;
	p = new wchar_t[len + 1];
	write(0, p, length, 0, s, len);
	return *this;
}

Text &Text::aquireText(const wchar_t *s, int len, bool deletePrevious)
{
	if (deletePrevious) delete p;
	length = len;
	p = new wchar_t[len + 1];
	write(0, p, length, 0, s, len);
	return *this;
}

Text &Text::appendText(const wchar_t *t, int len)
{
	int qlength = length + len;
	wchar_t *q = new wchar_t[qlength + 1];
	write(0, q, qlength + 1, 0, p, length);
	write(length, q, qlength + 1, 0, t, len);
	delete p;
	p = q;
	length = qlength;
	return *this;
}

Text &Text::appendText(const char *t, int len)
{
	int qlength = length + len;
	wchar_t *q = new wchar_t[qlength + 1];
	write(0, q, qlength + 1, 0, p, length);
	write(length, q, qlength + 1, 0, t, len);
	delete p;
	p = q;
	length = qlength;
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

Text::Text(const Text &t)
{
	aquireText(t.p, t.length, false);
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
	*r = 0;
	len = i;
}

void Text::GetWideString(wchar_t *buffer, int &len)
{
	write(0, buffer, len - 1, 0, p, length);
	len = len - 1 < length ? len - 1 : length;
}

int Text::GetMultibyteCharacterString(char *buffer)
{
	int mblen = wcsrtombs(NULL, (const wchar_t **)&p, 1, NULL);
	mblen = buffer ? wcsrtombs(buffer, (const wchar_t **)&p, mblen, NULL) : mblen;
	return mblen;
}

Text Text::FromMultibyteCharacterString(const char *buffer, int len)
{
	wchar_t *q = new wchar_t[len + 1];
	int mblen = mbsrtowcs(q, &buffer, len, NULL);
	
	Text t(q, mblen);
	delete q;
	return t;;
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
	if (ix < 0) throw TextException("Index out of bounds");
	if (ix + length > this->length) throw TextException("Text piece out of source Text");
	
	Text q;
	return q.aquireText(p + ix, length, true);
}

Text Text::Replace(Text &search, Text &replacement)
{
	TextBuffer tb(10000);
	int ix = 0;
	while (ix != -1 && ix < length) {
		int ixNow = FindIx(ix, search);
		if (ixNow == -1) ix = length;
		Text s = SubText(ix, ixNow - ix);
		tb.Append(s);
		if (ixNow < length) tb.Append(replacement);
		ix = ixNow + 1;
	}
	return tb.ToText();
}

Text Text::Replace(const wchar_t *search, const wchar_t *replacement)
{
	TextBuffer tb(10000);
	int ix = 0;
	while (ix < length) {
		int ixNow = FindIx(ix, search);
		if (ixNow == -1) ix = length;
		Text s = SubText(ix, ixNow - ix);
		tb.Append(s);
		if (ixNow < length) tb.Append(replacement);
		ix = ixNow + 1;
	}
	return tb.ToText();
}

Text Text::Replace(const char *search, const char *replacement)
{
	TextBuffer tb(10000);
	int ix = 0;
	while (ix < length) {
		int ixNow = FindIx(ix, search);
		if (ixNow == -1) ixNow = length;
		Text s = SubText(ix, ixNow - ix);
		tb.Append(s);
		if (ixNow < length) tb.Append(replacement);
		ix = ixNow + 1;
	}
	return tb.ToText();
}


int Text::FindIx(const Text &t)
{
	return findIx(0, p, length, 0, t.p, t.length);
}

int Text::FindIx(const char *t)
{
	int tlen = strlen(t);
	return findIx(0, p, length, 0, t, tlen);
}

int Text::FindIx(const wchar_t *t)
{
	int tlen = wcslen(t);
	return findIx(0, p, length, 0, t, tlen);
}

int Text::FindIx(Collection<char> &c)
{
	return FindIx(0, c);
}

int Text::FindIx(Collection<wchar_t> &c)
{
	return FindIx(0, c);
}

int Text::FindIx(int startIndex, const Text &t)
{
	return findIx(startIndex, p, length, 0, t.p, t.length);
}

int Text::FindIx(int startIndex, const char *t)
{
	int tlen = strlen(t);
	return findIx(startIndex, p, length, 0, t, tlen);
}

int Text::FindIx(int startIndex, const wchar_t *t)
{
	int tlen = wcslen(t);
	return findIx(startIndex, p, length, 0, t, tlen);
}

int Text::FindIx(int startIndex, Collection<char> &c) 
{
	for (int i=startIndex; i<length; i++) {
		if (c.Contains(p[i]))
			return i;
	}
	
	return -1;
}

int Text::FindIx(int startIndex, Collection<wchar_t> &c)
{
	for (int i=startIndex; i<length; i++) {
		if (c.Contains(p[i]))
			return i;
	}
	
	return -1;	
}

Text Text::TrimLeft(Collection<char> &c) 
{
	for (int i=0; i<length; i++) {
		if (c.Contains(p[i])) continue;
		return SubText(i);
	}
	
	return Text();
}

Text Text::TrimLeft(Collection<wchar_t> &c) 
{
	for (int i=0; i<length; i++) {
		if (c.Contains(p[i])) continue;
		return SubText(i);
	}
	
	return Text();
}

Text Text::TrimRight(Collection<char> &c) 
{
	for (int i = length - 1; i >= 0; i--) {
		if (c.Contains(p[i])) continue;
		return SubText(0, i + 1);
	}
	
	return Text();
}

Text Text::TrimRight(Collection<wchar_t> &c) 
{
	for (int i = length - 1; i >= 0; i--) {
		if (c.Contains(p[i])) continue;
		return SubText(0, i + 1);
	}
	
	return Text();
}

Text Text::Trim(Collection<char> &c) 
{
	for (int i=0; i<length; i++) {
		if (c.Contains(p[i])) continue;
		for (int j=length - 1; j>i; j--) {
			if (c.Contains(p[j])) continue;
			return SubText(i, j - i + 1);
		}
		break;
	}
	
	return Text();
}

Text Text::Trim(Collection<wchar_t> &c) 
{
	for (int i=0; i<length; i++) {
		if (c.Contains(p[i])) continue;
		for (int j=length - 1; j>i; j--) {
			if (c.Contains(p[j])) continue;
			return SubText(i, j - i + 1);
		}
		break;
	}
	
	return Text();
}

Text Text::ToUpper()
{
	Text t = *this;
	for (wchar_t *pp = t.p; *pp; pp++) *pp  = towupper(*pp);
	return t;
}

Text Text::ToLower()
{
	Text t = *this;
	for (wchar_t *pp = t.p; *pp; pp++) *pp  = towlower(*pp);
	return t;
}

Collection<int> &Text::ExtractIndexes(Collection<int> &destination, Text &textToFind)
{
	int ix = 0;
	
	while (ix < length) {
		ix = FindIx(ix, textToFind);
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
		ix = FindIx(ix, splitChars);
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

Collection<Text *> &Text::Split(Collection<Text *> &destination, Collection<wchar_t> &splitChars, bool removeEmptyEntries)
{
	int ix = 0, previx = 0;
	
	while (ix <= length) {
		ix = FindIx(ix, splitChars);
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
	Collection<wchar_t> cSplitChars(splitChars.p);
	return Split(destination, cSplitChars, removeEmptyEntries);
}

Collection<Text *> &Text::Split(Collection<Text *> &destination, char *splitChars, bool removeEmptyEntries)
{
	Collection<char> cSplitChars(splitChars);
	return Split(destination, cSplitChars, removeEmptyEntries);
}

Collection<Text *> &Text::Split(Collection<Text *> &destination, wchar_t *splitChars, bool removeEmptyEntries)
{
	Collection<wchar_t> cSplitChars(splitChars);
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

bool Text::Equals(const char *c)
{
	return *this == c;
}

bool Text::Equals(const wchar_t *c)
{
	return *this == c;
}

bool Text::StartsWith(Text &t)
{
	return StartsWith(t.p, t.length);
}

bool Text::StartsWith(const char *t)
{
	return StartsWith(t, strlen(t));
}

bool Text::StartsWith(const wchar_t *t)
{
	return StartsWith(t, wcslen(t));
}

bool Text::StartsWith(const char *t, int len)
{
	return findIx(0, p, length, 0, t, len) == 0;
}

bool Text::StartsWith(const wchar_t *t, int len)
{
	return findIx(0, p, length, 0, t, len) == 0;
}

bool Text::EndsWith(const Text &t)
{
	if (length < t.length) return -1;
	return findIx(length - t.length, p, length, 0, t.p, t.length) == length - t.length;
}

bool Text::EndsWith(const wchar_t *t)
{
	int tlen = wcslen(t);
	if (length < tlen) return false;
	return EndsWith(t, wcslen(t));
}

bool Text::EndsWith(const char *t)
{
	int tlen = strlen(t);
	if (length < tlen) return false;
	return EndsWith(t, strlen(t));
}

bool Text::EndsWith(const char *t, int len)
{
	if (length < len) return false;
	return findIx(length - len, p, length, 0, t, len) == length - len;
}

bool Text::EndsWith(const wchar_t *t, int len)
{
	if (length < len) return false;
	return findIx(length - len, p, length, 0, t, len) == length - len;
}

bool Text::Contains(const Text &t)
{
	return findIx(0, p, length, 0, t.p, t.length) != -1;
}

bool Text::Contains(const char *t)
{
	return findIx(0, p, length, 0, t, strlen(t)) != -1;
}

bool Text::Contains(const char *t, int len)
{
	return findIx(0, p, length, 0, t, len) != -1;
}

bool Text::Contains(const wchar_t *t)
{
	return findIx(0, p, length, 0, t, wcslen(t)) != -1;
}

bool Text::Contains(const wchar_t *t, int len)
{
	return findIx(0, p, length, 0, t, len) != -1;
}

Text Text::operator +(const Text &t)
{
	int qlength = length + t.length;
	wchar_t *q = new wchar_t[qlength + 1];
	write(0, q, qlength + 1, 0, p, length);
	write(length, q, qlength + 1, 0, t.p, t.length);
	
	Text tt;
	delete tt.p;
	tt.length = qlength;
	tt.p = q;
	return tt;
}

Text Text::operator +(const char *t)
{
	int tlength = strlen(t);
	int qlength = length + tlength;
	wchar_t *q = new wchar_t[qlength + 1];
	write(0, q, qlength + 1, 0, p, length);
	write(length, q, qlength + 1, 0, t, tlength);
	
	Text tt;
	delete tt.p;
	tt.length = qlength;
	tt.p = q;
	return tt;
}

Text Text::operator +(const wchar_t *t)
{
	int tlength = wcslen(t);
	int qlength = length + tlength;
	wchar_t *q = new wchar_t[qlength + 1];
	write(0, q, qlength + 1, 0, p, length);
	write(length, q, qlength + 1, 0, t, tlength);
	
	Text tt;
	delete tt.p;
	tt.length = qlength;
	tt.p = q;
	return tt;
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
