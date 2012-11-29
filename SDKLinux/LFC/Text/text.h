#ifndef TEXT_H
#define TEXT_H

#include "../n_object.h"
#include "../exception.h"
#include "../Collections/collection.h"


class Text : public NObject {
	
private:
	wchar_t *p;
	int length;
	
	Text &aquireText(const char *s, int len, bool deletePrevious);
	Text &aquireText(const wchar_t *s, int len, bool deletePrevious);
	Text &appendText(const char *t, int len);
	Text &appendText(const wchar_t *t, int len);
	Text &joinText(const wchar_t *t, int tlen, const char *u, int ulen, bool deletePrevious);
	Text &joinText(const wchar_t *t, int tlen, const wchar_t *u, int ulen, bool deletePrevious);
	int findIx(const char *c, int len);
	int findIx(const wchar_t *c, int len);
	
public:
	Text();
	Text(const char *t);
	Text(const char *t, int len);
	Text(const wchar_t *t);
	Text(const wchar_t *t, int len);
	Text(const wchar_t *t, int tlen, const wchar_t *u, int ulen);
	Text(const Text &t);
	Text(const Text &u, const Text &v);
	Text(bool b);
	Text(char c);
	Text(wchar_t c);
	Text(short int i);
	Text(int i);
	Text(long int i);
	Text(float f);
	Text(double d);
	virtual ~Text();

	int Length();
	void GetAnsiString(char *buffer, int &len);
	void GetWideString(wchar_t *buffer, int &len);
	int Compare(const Text &t);
	int Compare(const char *t);
	int Compare(const char *t, int len);
	int Compare(const wchar_t *t);
	int Compare(const wchar_t *t, int len);
	Text SubText(int ix);
	Text SubText(int ix, int length);
	//Text Replace(Text &search, Text &replacement);
	int FindIx(const Text &t);
	int FindIx(const char *t);
	int FindIx(Collection<char> &c);
	int FindIx(const Text &t, int startIndex);
	int FindIx(const char *t, int startIndex);
	int FindIx(Collection<char> &c, int startIndex);
	Collection<int> &ExtractIndexes(Collection<int> &destination, Text &textToFind);
	Collection<Text *> &Split(Collection<Text *> &destination, Collection<char> &splitChars, bool removeEmptyEntries);
	Collection<Text *> &Split(Collection<Text *> &destination, Text &splitChars, bool removeEmptyEntries);
	void Print();
	bool Equals(const Text &t);
	bool Equals(const char *c);
	bool StartsWith(Text &t);
	bool StartsWith(const char *c);
	bool StartsWith(const char *c, int len);
	bool StartsWith(const wchar_t *c);
	bool StartsWith(const wchar_t *c, int len);
	bool EndsWith(const Text &t);
	bool EndsWith(const char *t);
	bool EndsWith(const char *t, int len);
	bool EndsWith(const wchar_t *t);
	bool EndsWith(const wchar_t *t, int len);
	bool Contains(const Text &t);
	bool Contains(const char *t);
	bool Contains(const char *t, int len);
	bool Contains(const wchar_t *t);
	bool Contains(const wchar_t *t, int len);
	
	Text operator+(const Text &t);
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
	Text &operator+=(const Text &t);
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
	Text &operator=(const Text &t);
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
	bool operator==(const Text &t);
	bool operator==(const char *t);
	bool operator==(const wchar_t *t);
	bool operator!=(const Text &t);
	bool operator!=(const char *t);
	bool operator!=(const wchar_t *t);
	bool operator<(const Text &t);
	bool operator<(const char *t);
	bool operator<(const wchar_t *t);
	bool operator>(const Text &t);
	bool operator>(const char *t);
	bool operator>(const wchar_t *t);
	bool operator<=(const Text &t);
	bool operator<=(const char *t);
	bool operator<=(const wchar_t *t);
	bool operator>=(const Text &t);
	bool operator>=(const char *t);
	bool operator>=(const wchar_t *t);
	wchar_t &operator[](const int ix);

};

#endif // TEXT_H
