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
   
   
#ifndef TEXT_H
#define TEXT_H

#include "../n_object.h"
#include "../exception.h"
#include "../Collections/collection.h"

class Locale;
class TextBuffer;
class Directory;
class DateTime;
class StdOut;

class Text : public NObject {
	
	friend class Locale;
	friend class TextBuffer;
	friend class Directory;
	friend class DateTime;
	friend class StdOut;
	
private:
	wchar_t *p;
	int length;
	
	Text &aquireText(const char *s, int len, bool deletePrevious);
	Text &aquireText(const wchar_t *s, int len, bool deletePrevious);
	Text &appendText(const char *t, int len);
	Text &appendText(const wchar_t *t, int len);


public:

	static int write(int posdest, wchar_t *dest, int ldest, int possrc, const char *src, int lsrc);
	static int write(int posdest, wchar_t *dest, int ldest, int possrc, const wchar_t *src, int lsrc);
	static int findIx(int strpos, const wchar_t *str, int strlen, int findpos, const wchar_t *find, int findlen);
	static Text FromErrno();
	static Text Join(const Collection<Text *> &tokens, const Text &separator);

	Text();
	Text(const NObject &o);
	Text(const NObject *o);
	Text(const char *t);
	Text(const char *t, int len);
	Text(const wchar_t *t);
	Text(const wchar_t *t, int len);
	Text(const Text &t);
	Text(const Text *t);
	Text(bool b);
	Text(char c);
	Text(wchar_t c);
	Text(short int i);
	Text(int i);
	Text(unsigned int i);
	Text(long int i);
	Text(unsigned long int i);
	Text(float f);
	Text(double d);
	Text(long double d);
	virtual ~Text();

	int Length();
	int GetAnsiString(char *buffer, int len);
	int GetWideString(wchar_t *buffer, int len);
	int Compare(const Text &t);
	Text SubText(int ix);
	Text SubText(int ix, int length);
	Text Replace(const Text &search, const Text &replacement);
	int FindIx(const Text &t);
	int FindIx(const Collection<char> &c);
	int FindIx(const Collection<wchar_t> &c);
	int FindIx(int startIndex, const Text &t);
	int FindIx(int startIndex, const Collection<char> &c);
	int FindIx(int startIndex, const Collection<wchar_t> &c);
	Text TrimLeft(const Collection<char> &c);
	Text TrimRight(const Collection<char> &c);
	Text Trim(const Collection<char> &c);
	Text TrimLeft(const Collection<wchar_t> &c);
	Text TrimRight(const Collection<wchar_t> &c);
	Text Trim(const Collection<wchar_t> &c);
	Text ToUpper();
	Text ToLower();
	Collection<int> ExtractIndexes(Text &textToFind);
	Collection<Text *> Split(const Text &splitChars, bool removeEmptyEntries);
	bool Equals(const Text &t);
	bool StartsWith(const Text &t);
	bool EndsWith(const Text &t);
	bool Contains(const Text &t);
	
	Text operator+(const Text &t);
	Text &operator+=(const Text &t);
	Text &operator=(const Text &t);
	bool operator==(const Text &t);
	bool operator!=(const Text &t);
	bool operator<(const Text &t);
	bool operator>(const Text &t);
	bool operator<=(const Text &t);
	bool operator>=(const Text &t);
	wchar_t &operator[](const int ix);
	
	static int COMPARER(const void *u, const void *v);

	virtual NObject *NewInstance();
	virtual Text ToText();
	virtual int Compare(const NObject &o);
	virtual void Serialize(const Serializator &s);
	virtual void Deserialize(const Serializator &s);
	
	bool CheckRegExpr(const Text &expr, bool ignoreCase);
	Collection<Text *> GetRegExprMatches(const Text &expr, bool ignoreCase);

};

#endif // TEXT_H
