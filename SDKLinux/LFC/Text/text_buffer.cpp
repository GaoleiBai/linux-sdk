#include "text_buffer.h"
#include "text_exception.h"
#include <string.h>
#include <wchar.h>

TextBuffer::TextBuffer()
{
	p = new wchar_t[10000];
	psize = 1000;
	length = 0;
}

TextBuffer::TextBuffer(int size)
{
	if (size <= 0) throw new TextException("Size ");
	p = new wchar_t[size];
	psize = size;
	length = 0;
}

TextBuffer::TextBuffer(Text &t)
{
	length = t.Length();
	psize = length + 10000;
	p = new wchar_t[psize];
	t.GetWideString(p, psize);
}

TextBuffer::TextBuffer(const char *t)
{
	length = strlen(t);
	psize = length + 10000;
	p = new wchar_t[psize];
	wchar_t *pp = p;
	char *tt = (char *)t;
	for (int i=0; i<length; i++) *pp++ = *tt++;
	*pp = 0;
}

TextBuffer::TextBuffer(const wchar_t *t)
{
	length = wcslen(t);
	psize = length + 10000;
	p = new wchar_t[psize];
	wchar_t *pp = p;
	wchar_t *tt = (wchar_t *)t;
	for (int i=0; i<length; i++) *pp++ = *tt++;
	*pp = 0;
}

TextBuffer::~TextBuffer()
{
	delete p;
}

void TextBuffer::increaseBuffer(int newLen)
{
	if (newLen >= psize) {
		int qsize = 2 * psize + newLen;
		wchar_t *q = new wchar_t[qsize];
		wchar_t *qq = q;
		wchar_t *pp = p;
		for (int i=0; i<length; i++) *qq++ = *pp++;
		*qq = 0;
		delete p;
		p = q;
		psize = qsize;
	}
}

void TextBuffer::Append(Text &t)
{
	increaseBuffer(length + t.Length());
	
	int len = psize - length - 1;
	t.GetWideString(p + length, len);
	length += t.Length();
}

void TextBuffer::Append(const char *t)
{
	int tlen = strlen(t);
	increaseBuffer(length + tlen);
	
	wchar_t *pp = p + length;
	char *tt = (char *)t;
	for (int i=0; i<tlen; i++) *pp++ = *tt++;
	*pp = 0;
	length += tlen;
}

void TextBuffer::Append(const wchar_t *t)
{
	int tlen = wcslen(t);
	increaseBuffer(length + tlen);
	
	wchar_t *pp = p + length;
	wchar_t *tt = (wchar_t *)t;
	for (int i=0; i<tlen; i++) *pp++ = *tt++;
	*pp = 0;	
	length += tlen;
}

Text TextBuffer::ToText()
{
	Text t(p);
	return t;
}
