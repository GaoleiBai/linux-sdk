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
   
   
#include "testnumeric.h"
#include "../LFC/LFC.h"

TestNumeric::TestNumeric()
{
}

TestNumeric::~TestNumeric()
{
}

int TestNumeric::Perform()
{
	NBool b = false;
	
	NChar c = 'c';
	NShort s = 5001;
	NInt i = 2345678;
	NLong l = 200167896;
	NLongLong ll = 200167896345;
	
	NUChar uc = 'c';
	NUShort us = 5001;
	NUInt ui = 2345678;
	NULong ul = 200167896;
	NULongLong ull = 200167896345;

	NChar mc = -'c';
	NShort ms = -5001;
	NInt mi = -2345678;
	NLong ml = -200167896;
	NLongLong mll = -200167896345;
	
	NFloat f = -1234.5f;
	NDouble d = 128.765567;
	NLongDouble ld = -1e300l;
	
	try {
		if (b.Value() != false) throw new Exception("NBool error", __FILE__, __LINE__, __func__);
		
		if (c.Value() != 'c') throw new Exception("NChar error", __FILE__, __LINE__, __func__);
		if (s.Value() != 5001) throw new Exception("NShort error", __FILE__, __LINE__, __func__);
		if (i.Value() != 2345678) throw new Exception("NInt error", __FILE__, __LINE__, __func__);
		if (l.Value() != 200167896) throw new Exception("NLong error", __FILE__, __LINE__, __func__);
		if (ll.Value() != 200167896345) throw new Exception("NLongLong error", __FILE__, __LINE__, __func__);

		if (uc.Value() != 'c') throw new Exception("NUChar error", __FILE__, __LINE__, __func__);
		if (us.Value() != 5001) throw new Exception("NUShort error", __FILE__, __LINE__, __func__);
		if (ui.Value() != 2345678) throw new Exception("NUInt error", __FILE__, __LINE__, __func__);
		if (ul.Value() != 200167896) throw new Exception("NULong error", __FILE__, __LINE__, __func__);
		if (ull.Value() != 200167896345) throw new Exception("NULongLong error", __FILE__, __LINE__, __func__);
		
		if (mc.Value() != -'c') throw new Exception("NChar error", __FILE__, __LINE__, __func__);
		if (ms.Value() != -5001) throw new Exception("NShort error", __FILE__, __LINE__, __func__);
		if (mi.Value() != -2345678) throw new Exception("NInt error", __FILE__, __LINE__, __func__);
		if (ml.Value() != -200167896) throw new Exception("NLong error", __FILE__, __LINE__, __func__);
		if (mll.Value() != -200167896345) throw new Exception("NLongLong error", __FILE__, __LINE__, __func__);
		
		if (f.Value() != -1234.5f) throw new Exception("NFLoat error", __FILE__, __LINE__, __func__);
		if (d.Value() != 128.765567) throw new Exception("NDouble error", __FILE__, __LINE__, __func__);
		if (ld.Value() != -1e300l) throw new Exception("NLongDouble error", __FILE__, __LINE__, __func__);
		
		NBool b1;
		b1 = NBool::Parse("true");
		if (b1.Value() != true) throw new Exception("NBool::Parse error", __FILE__, __LINE__, __func__);
		b1 = NBool::Parse("false");
		if (b1.Value() != false) throw new Exception("NBool::Parse error", __FILE__, __LINE__, __func__);
		try { b1 = NBool::Parse("porca miseria!!!"); StdOut::PrintLine("NBool cannot parse wrong string"); return -1; }
		catch (Exception *e) { delete e; }
		
		NLongLong nll1;
		NChar c1;
		for (int i=-128; i<=127; i++) {
			nll1 = (NLongLong)i;
			c1 = NChar::Parse(nll1.ToText());
			if (c1.ToText("%d") != nll1.ToText()) throw new Exception("NChar::ToText error", __FILE__, __LINE__, __func__);
		}
		char sc;
		if (NChar::TryParse("-129", sc)) { StdOut::PrintLine("NChar cannot parse '-129'"); return -1; }
		if (NChar::TryParse("128", sc)) { StdOut::PrintLine("NChar cannot parse '128'"); return -1; }
		if (NChar::MaxValue() != 127) throw new Exception("NChar::MaxValue error", __FILE__, __LINE__, __func__);
		if (NChar::MinValue() != -128) throw new Exception("NChar::MinValue error", __FILE__, __LINE__, __func__);
		
		NShort s1;
		for (int i=-32768; i<=32767; i++) {
			nll1 = (NLongLong)i;
			s1 = NShort::Parse(nll1.ToText());
			if (s1.ToText() != nll1.ToText()) throw new Exception("NShort::ToText error", __FILE__, __LINE__, __func__);
		}
		short ss;
		if (NShort::TryParse("-32769", ss)) { StdOut::PrintLine("NShort cannot parse -32769"); return -1; }
		if (NShort::TryParse("32768", ss)) { StdOut::PrintLine("NShort cannot parse 32768"); return -1; }
		if (NShort::MaxValue() != 32767) throw new Exception("NShort::MaxValue error", __FILE__, __LINE__, __func__);
		if (NShort::MinValue() != -32768) throw new Exception("NShort::MinValue error", __FILE__, __LINE__, __func__);
		
		
		int kk = 1;
	} catch (Exception *e) {
		delete e;
	}

	return 0;
}

