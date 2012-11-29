#include "text_buffer.h"
#include "text_exception.h"
#include <string.h>
#include <wchar.h>

TextBuffer::TextBuffer()
{
	p = new wchar_t[1000];
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
	psize = length + 1000;
	p = new wchar_t[psize];
	t.GetWideString(p, psize);
}

TextBuffer::TextBuffer(const char *t)
{
	length = strlen(t);
	psize = length + 1000;
	p = new wchar_t[psize];
	wchar_t *pp = p;
	char *tt = (char *)t;
	for (int i=0; i<length; i++) *pp++ = *tt++;
}

TextBuffer::TextBuffer(const wchar_t *t)
{
	length = wcslen(t);
	psize = length + 1000;
	p = new wchar_t[psize];
	wchar_t *pp = p;
	wchar_t *tt = (wchar_t *)t;
	for (int i=0; i<length; i++) *pp++ = *tt++;	
}

TextBuffer::~TextBuffer()
{
	delete p;
}

