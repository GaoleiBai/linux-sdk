#ifndef TEXT_H
#define TEXT_H

#include "../n_object.h"
#include "../exception.h"
#include "../Collections/collection.h"

class Text : public NObject {
	
private:
	char *p;
	int length;
	
	Text &aquireText(const char *s, int length, bool deletePrevious);
	int findIx(const char *c, int len);
	
public:
	Text();
	Text(const char *t);
	Text(const char *t, int length);
	Text(const Text &t);
	Text(bool b);
	Text(int i);
	Text(float f);
	Text(double d);
	virtual ~Text();

	int Length();
	void GetAnsiString(char *buffer, int &len);
	int Compare(const Text &t);
	int Compare(const char *t);
	Text SubText(int ix);
	Text SubText(int ix, int length);
	//static Text &ReplaceText(Text &cadena, Text &replacementString);
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
	bool EndsWith(const Text &t);
	bool EndsWith(const char *t);
	bool EndsWith(const char *t, int len);
	bool Contains(const Text &t);
	bool Contains(const char *t);
	bool Contains(const char *t, int len);
	
	Text operator+(const Text &t);
	Text operator+(const char *t);
	Text operator+(bool b);
	Text operator+(int i);
	Text operator+(float f);
	Text operator+(double d);
	Text &operator+=(const Text &t);
	Text &operator+=(const char *t);
	Text &operator+=(bool b);
	Text &operator+=(int i);
	Text &operator+=(float f);
	Text &operator+=(double d);
	Text &operator=(const Text &t);
	Text &operator=(const char *t);
	Text &operator=(bool b);
	Text &operator=(int i);
	Text &operator=(float f);
	Text &operator=(double d);
	bool operator==(const Text &t);
	bool operator==(const char *t);
	bool operator!=(const Text &t);
	bool operator!=(const char *t);
	bool operator<(const Text &t);
	bool operator<(const char *t);
	bool operator>(const Text &t);
	bool operator>(const char *t);
	char &operator[](const int ix);

};

#endif // TEXT_H
