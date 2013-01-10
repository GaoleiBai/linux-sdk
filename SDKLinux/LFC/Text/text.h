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

	static int write(int posdest, char *dest, int ldest, int possrc, const char *src, int lsrc);
	static int write(int posdest, wchar_t *dest, int ldest, int possrc, const char *src, int lsrc);
	static int write(int posdest, wchar_t *dest, int ldest, int possrc, const wchar_t *src, int lsrc);
	static int findIx(int strpos, const wchar_t *str, int strlen, int findpos, const char *find, int findlen);
	static int findIx(int strpos, const wchar_t *str, int strlen, int findpos, const wchar_t *find, int findlen);
	static Text FromErrno();
	static Text Join(const Collection<Text *> &tokens, const Text &separator);

	Text();
	Text(NObject &o);
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
	virtual ~Text();

	int Length();
	int GetAnsiString(char *buffer, int len);
	int GetWideString(wchar_t *buffer, int len);
	int Compare(const NObject &o);
	int Compare(const Text &t);
	int Compare(const char *t);
	int Compare(const wchar_t *t);
	int Compare(const char *t, int len);
	int Compare(const wchar_t *t, int len);
	Text SubText(int ix);
	Text SubText(int ix, int length);
	Text Replace(Text &search, Text &replacement);
	Text Replace(const wchar_t *search, const wchar_t *replacement);
	Text Replace(const char *search, const char *replacement);
	int FindIx(const Text &t);
	int FindIx(const char *t);
	int FindIx(const wchar_t *t);
	int FindIx(const Collection<char> &c);
	int FindIx(const Collection<wchar_t> &c);
	int FindIx(int startIndex, const Text &t);
	int FindIx(int startIndex, const char *t);
	int FindIx(int startIndex, const wchar_t *t);
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
	Text ToText();
	Collection<int> ExtractIndexes(Text &textToFind);
	Collection<Text *> Split(const Collection<char> &splitChars, bool removeEmptyEntries);
	Collection<Text *> Split(const Collection<wchar_t> &splitChars, bool removeEmptyEntries);
	Collection<Text *> Split(const Text &splitChars, bool removeEmptyEntries);
	Collection<Text *> Split(const char *splitChars, bool removeEmptyEntries);
	Collection<Text *> Split(const wchar_t *splitChars, bool removeEmptyEntries);
	bool Equals(const Text &t);
	bool Equals(const char *c);
	bool Equals(const wchar_t *c);
	bool StartsWith(Text &t);
	bool StartsWith(const char *c);
	bool StartsWith(const wchar_t *c);
	bool StartsWith(const char *c, int len);
	bool StartsWith(const wchar_t *c, int len);
	bool EndsWith(const Text &t);
	bool EndsWith(const char *t);
	bool EndsWith(const wchar_t *t);
	bool EndsWith(const char *t, int len);
	bool EndsWith(const wchar_t *t, int len);
	bool Contains(const Text &t);
	bool Contains(const char *t);
	bool Contains(const wchar_t *t);
	bool Contains(const char *t, int len);
	bool Contains(const wchar_t *t, int len);
	
	Text operator+(const Text &t);
	/*
	Text operator+(const char *t);
	Text operator+(const wchar_t *t);
	Text operator+(bool b);
	Text operator+(char c);
	Text operator+(wchar_t c);
	Text operator+(short int i);
	Text operator+(int i);
	Text operator+(long int i);
	Text operator+(float f);
	Text operator+(double d);
	 */
	Text &operator+=(const Text &t);
	/*
	Text &operator+=(const char *t);
	Text &operator+=(const wchar_t *t);
	Text &operator+=(bool b);
	Text &operator+=(char c);
	Text &operator+=(wchar_t c);
	Text &operator+=(short int i);
	Text &operator+=(int i);
	Text &operator+=(long int i);
	Text &operator+=(float f);
	Text &operator+=(double d);
	 */
	Text &operator=(const Text &t);
	 /*
	Text &operator=(const char *t);
	Text &operator=(const wchar_t *t);
	Text &operator=(bool b);
	Text &operator=(char c);
	Text &operator=(wchar_t c);
	Text &operator=(short int i);
	Text &operator=(int i);
	Text &operator=(long int i);
	Text &operator=(float f);
	Text &operator=(double d);
	 * */
	bool operator==(const Text &t);
	/*
	bool operator==(const char *t);
	bool operator==(const wchar_t *t);
	 */
	bool operator!=(const Text &t);
	/*
	bool operator!=(const char *t);
	bool operator!=(const wchar_t *t);
	 */
	bool operator<(const Text &t);
	/*
	bool operator<(const char *t);
	bool operator<(const wchar_t *t);
	 */
	bool operator>(const Text &t);
	/*
	bool operator>(const char *t);
	bool operator>(const wchar_t *t);
	 */
	bool operator<=(const Text &t);
	/*
	bool operator<=(const char *t);
	bool operator<=(const wchar_t *t);
	 */
	bool operator>=(const Text &t);
	/*
	bool operator>=(const char *t);
	bool operator>=(const wchar_t *t);
	 */
	wchar_t &operator[](const int ix);
	
	static int COMPARER(const void *u, const void *v);

};

#endif // TEXT_H
