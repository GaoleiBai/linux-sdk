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
   
   
#include "text.h"
#include "text_buffer.h"
#include "text_exception.h"
#include "../Encoding/locale_encoding.h"
#include "../FileSystem/serializator.h"
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <errno.h>
#include <regex.h>

int Text::write(int posdest, char *dest, int ldest, int possrc, const char *src, int lsrc)
{
	int lldest = ldest;
	if (lsrc < ldest - posdest) lldest = posdest + lsrc;
	char *dd = dest + posdest;
	char *ss = (char *)src;
	for (int i=posdest; i<lldest; i++) *dd++ = *ss++;
	*dd = 0;
	return lldest - posdest;
}

int Text::write(int posdest, wchar_t *dest, int ldest, int possrc, const char *src, int lsrc)
{
	int lldest = ldest;
	if (lsrc < ldest - posdest) lldest = posdest + lsrc;
	wchar_t *dd = dest + posdest;
	char *ss = (char *)src;
	int written = 0;
	int size = 0;
	for (int i = posdest; i<lldest; i += size) {
		size = mbtowc(dd, ss, 10);
		if (size == -1) 
		{
			throw new TextException("The current locale doesn't allow to translate the characters.", __FILE__, __LINE__, __func__);
		}
		dd++;
		ss += size;
		written++;
	}
	*dd = 0;
	return written;
}

int Text::write(int posdest, wchar_t *dest, int ldest, int possrc, const wchar_t *src, int lsrc)
{
	int lldest = ldest;
	if (lsrc < ldest - posdest) lldest = posdest + lsrc;
	wchar_t *dd = dest + posdest;
	wchar_t *ss = (wchar_t *)src;
	for (int i=posdest; i<lldest; i++) *dd++ = *ss++;
	*dd = 0;
	return lldest - posdest;
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
	p = new wchar_t[len + 1];
	length = write(0, p, len, 0, s, len);
	return *this;
}

Text &Text::aquireText(const wchar_t *s, int len, bool deletePrevious)
{
	if (deletePrevious) delete p;
	p = new wchar_t[len + 1];
	length = write(0, p, len, 0, s, len);
	return *this;
}

Text &Text::appendText(const wchar_t *t, int len)
{
	int qlength = length + len;
	wchar_t *q = new wchar_t[qlength + 1];
	length = write(0, q, qlength + 1, 0, p, length);
	length += write(length, q, qlength + 1, 0, t, len);
	delete p;
	p = q;
	return *this;
}

Text &Text::appendText(const char *t, int len)
{
	int qlength = length + len;
	wchar_t *q = new wchar_t[qlength + 1];
	length = write(0, q, qlength + 1, 0, p, length);
	length += write(length, q, qlength + 1, 0, t, len);
	delete p;
	p = q;
	return *this;
}

Text::Text()
{
	aquireText("", 0, false);
}

Text::Text(const NObject &o)
{
	Text t = ((NObject *)&o)->ToText();
	aquireText(t.p, t.length, false);
}

Text::Text(const NObject *o)
{
	Text t = ((NObject *)o)->ToText();
	aquireText(t.p, t.length, false);
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

Text::Text(const Text *t)
{
	aquireText(t->p, t->length, false);
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

Text::Text(unsigned int i)
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

Text::Text(unsigned long int i)
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

Text::Text(long double d)
{
	char cadena[100];
	sprintf(cadena, "%Lf", d);
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

int Text::GetAnsiString(char *buffer, int len)
{
	wchar_t *q = p;
	char *r = buffer;
	char test[10];
	int i = 0;
	while (i < len - 1 && *q) {
		int size = wctomb(test, *q);
		if (i + size >= len) break;
		if (size == -1) throw new TextException("Can't translate characters with the current locale.", __FILE__, __LINE__, __func__);
		for (int j=0; j<size; j++) r[j] = test[j];
		i += size;
		r += size;
		q++;
	}
	*r = 0;
	len = i;
}

int Text::GetWideString(wchar_t *buffer, int len)
{
	return write(0, buffer, len - 1, 0, p, length);
}

int Text::Compare(const NObject &o)
{
	return Compare(((NObject *)&o)->ToText());
}

int Text::Compare(const char *t)
{
	return Compare(t, strlen(t));
}

int Text::Compare(const wchar_t *t)
{
	return Compare(t, wcslen(t));
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
	return lenDiff;
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
	if (ix < 0) throw new TextException("Index out of bounds", __FILE__, __LINE__, __func__);
	if (ix + length > this->length) throw new TextException("Text piece out of source Text", __FILE__, __LINE__, __func__);
	
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

int Text::FindIx(const Collection<char> &c)
{
	return FindIx(0, c);
}

int Text::FindIx(const Collection<wchar_t> &c)
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

int Text::FindIx(int startIndex, const Collection<char> &c) 
{
	for (int i=startIndex; i<length; i++) {
		if (((Collection<char> *)&c)->Contains(p[i]))
			return i;
	}
	
	return -1;
}

int Text::FindIx(int startIndex, const Collection<wchar_t> &c)
{
	for (int i=startIndex; i<length; i++) {
		if (((Collection<wchar_t> *)&c)->Contains(p[i]))
			return i;
	}
	
	return -1;	
}

Text Text::TrimLeft(const Collection<char> &c) 
{
	for (int i=0; i<length; i++) {
		if (((Collection<char> *)&c)->Contains(p[i])) continue;
		return SubText(i);
	}
	
	return Text();
}

Text Text::TrimLeft(const Collection<wchar_t> &c) 
{
	for (int i=0; i<length; i++) {
		if (((Collection<wchar_t> *)&c)->Contains(p[i])) continue;
		return SubText(i);
	}
	
	return Text();
}

Text Text::TrimRight(const Collection<char> &c) 
{
	for (int i = length - 1; i >= 0; i--) {
		if (((Collection<char> *)&c)->Contains(p[i])) continue;
		return SubText(0, i + 1);
	}
	
	return Text();
}

Text Text::TrimRight(const Collection<wchar_t> &c) 
{
	for (int i = length - 1; i >= 0; i--) {
		if (((Collection<wchar_t> *)&c)->Contains(p[i])) continue;
		return SubText(0, i + 1);
	}
	
	return Text();
}

Text Text::Trim(const Collection<char> &c) 
{
	Collection<char> *cc = (Collection<char> *)&c;
	
	for (int i=0; i<length; i++) {
		if (cc->Contains(p[i])) continue;
		for (int j=length - 1; j>i; j--) {
			if (cc->Contains(p[j])) continue;
			return SubText(i, j - i + 1);
		}
		break;
	}
	
	return *this;
}

Text Text::Trim(const Collection<wchar_t> &c) 
{
	Collection<wchar_t> *cc = (Collection<wchar_t> *)&c;

	for (int i=0; i<length; i++) {
		if (cc->Contains(p[i])) continue;
		for (int j=length - 1; j>i; j--) {
			if (cc->Contains(p[j])) continue;
			return SubText(i, j - i + 1);
		}
		break;
	}
	
	return *this;
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

Text Text::ToText()
{
	return *this;
}

Collection<int> Text::ExtractIndexes(Text &textToFind)
{
	Collection<int> result;
	int ix = 0;
	
	while (ix < length) {
		ix = FindIx(ix, textToFind);
		if (ix == -1) break;
		result.Add(ix);
		ix += textToFind.length;
	}
	
	return result;
}

Collection<Text *> Text::Split(const Collection<char> &splitChars, bool removeEmptyEntries)
{
	Collection<Text *> result;
	int ix = 0, previx = 0;
	
	while (ix <= length) {
		ix = FindIx(ix, splitChars);
		if (ix == -1) ix = length;
		if (ix == previx) {
			if (!removeEmptyEntries) result.Add(new Text());
		} else {
			result.Add(new Text(p + previx, (int)(ix - previx)));
		}
		ix++;
		previx = ix;
	}
	
	return result;
}

Collection<Text *> Text::Split(const Collection<wchar_t> &splitChars, bool removeEmptyEntries)
{
	Collection<Text *> result;
	int ix = 0, previx = 0;
	
	while (ix <= length) {
		ix = FindIx(ix, splitChars);
		if (ix == -1) ix = length;
		if (ix == previx) {
			if (!removeEmptyEntries) result.Add(new Text());
		} else {
			if (ix == 0) result.Add(new Text(""));	// Splitchar at the beginning
			result.Add(new Text(p + previx, (int)(ix - previx)));
		}
		ix++;
		previx = ix;
	}
	
	return result;
}

Collection<Text *> Text::Split(const Text &splitChars, bool removeEmptyEntries)
{
	Collection<wchar_t> cSplitChars(splitChars.p);
	return Split(cSplitChars, removeEmptyEntries);
}

Collection<Text *> Text::Split(const char *splitChars, bool removeEmptyEntries)
{
	Collection<char> cSplitChars(splitChars);
	return Split(cSplitChars, removeEmptyEntries);
}

Collection<Text *> Text::Split(const wchar_t *splitChars, bool removeEmptyEntries)
{
	Collection<wchar_t> cSplitChars(splitChars);
	return Split(cSplitChars, removeEmptyEntries);
}

Text Text::Join(const Collection<Text *> &tokens, const Text &separator)
{
	Collection<Text *> *c = (Collection<Text *> *)&tokens;
	if (c->Count() == 0) return "";
	TextBuffer b;
	b.Append((*c)[0]);
	for (int i=1; i<c->Count(); i++) {
		b.Append(separator);
		b.Append((*c)[i]);
	}
	return b.ToText();
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

Text Text::FromErrno()
{
	return Text(strerror(errno));
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

Text &Text::operator +=(const Text &t)
{
	return appendText(t.p, t.length);
}

Text &Text::operator =(const Text &t)
{
	if (&t == this) return *this;
	return aquireText(t.p, t.length, true);
}

bool Text::operator ==(const Text &t)
{
	if (&t == this) return true;
	if (length != t.length) return false;
	return Compare(t) == 0;
}

bool Text::operator !=(const Text &t)
{
	return !(*this == t);
}

bool Text::operator <(const Text &t)
{
	return Compare(t) < 0;
}

bool Text::operator >(const Text &t)
{
	return Compare(t) > 0;
}

bool Text::operator <=(const Text &t)
{
	return Compare(t) <= 0;
}

bool Text::operator >=(const Text &t)
{
	return Compare(t) >= 0;
}

wchar_t &Text::operator [](const int ix)
{
	if (ix < 0 || ix >= length) throw new TextException("Índice fuera de límites", __FILE__, __LINE__, __func__);
	return p[ix];
}

int Text::COMPARER(const void *u, const void *v)
{
	Text **uu = (Text **)u;
	Text **vv = (Text **)v;
	return (*uu)->Compare(**vv);
}

NObject *Text::NewInstance()
{
	return new Text();
}

void Text::Serialize(const Serializator &s)
{
	((Serializator *)&s)->Put(length);
	((Serializator *)&s)->Put((char *)p, sizeof(wchar_t) * length);
}

void Text::Deserialize(const Serializator &s)
{
	length = ((Serializator *)&s)->GetInt();
	delete p;
	p = new wchar_t[length + 1];
	((Serializator *)&s)->Get((char *)p, sizeof(wchar_t) * length);
	p[length] = 0;
}

bool Text::CheckRegExpr(const Text &expr, bool ignoreCase)
{
	regex_t re;
	char *ee = new char[2 * ((Text *)&expr)->Length() + 2];
	char *pp = new char[2 * length + 2];
	
	((Text *)&expr)->GetAnsiString(ee, ((Text *)&expr)->Length());
	GetAnsiString(pp, length);
	
	bool res = regcomp(&re, ee, ignoreCase ? REG_EXTENDED | REG_NOSUB | REG_ICASE : REG_EXTENDED | REG_NOSUB ) == 0;
	if (res) res = regexec(&re, pp, 0, NULL, 0);
	regfree
	(&re);
	
	delete ee;
	delete pp;
	return res;
}

Collection<Text *> Text::GetRegExprMatches(const Text &expr, bool ignoreCase)
{
	Collection<Text *> col(10);
	regex_t re;
	regmatch_t rm;
	char *ee = new char[2 * ((Text *)&expr)->Length() + 2];
	char *pp = new char[2 * length + 2];
	
	((Text *)&expr)->GetAnsiString(ee, ((Text *)&expr)->Length());
	GetAnsiString(pp, length);

	bool res = regcomp(&re, ee, ignoreCase ? REG_EXTENDED | REG_ICASE : REG_EXTENDED ) == 0;
	while (res) {
		res = regexec(&re, pp, 1, &rm, 0);
		col.Add(new Text(pp + rm.rm_so, rm.rm_eo - rm.rm_so));
	}
	regfree(&re);
	
	delete ee;
	delete pp;
	return col;
}